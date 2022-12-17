#include "mainwindow.h"

#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

Qt3DCore::QEntity * createScene() {

    Qt3DCore::QEntity *resultEntity = new Qt3DCore::QEntity;

    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh(resultEntity);

    torusMesh->setRadius(15.0f);
    torusMesh->setMinorRadius(6.0f);
    torusMesh->setSlices(16);
    torusMesh->setRings(100);

    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial(resultEntity);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform(resultEntity);

    resultEntity->addComponent(torusMesh);
    resultEntity->addComponent(torusMaterial);
    resultEntity->addComponent(torusTransform);


    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(resultEntity);
    Qt3DRender::QPointLight *pointLight = new Qt3DRender::QPointLight(lightEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(resultEntity);
    lightTransform->setTranslation(QVector3D(0.0f, 0.0f, 30.0f));
    lightEntity->addComponent(pointLight);
    lightEntity->addComponent(lightTransform);


    Qt3DCore::QEntity *cylEntity = new Qt3DCore::QEntity(resultEntity);

    Qt3DExtras::QCylinderMesh *cylinderMesh = new Qt3DExtras::QCylinderMesh(cylEntity);

    Qt3DCore::QTransform *cylTransform = new Qt3DCore::QTransform(resultEntity);
    cylTransform->setTranslation(QVector3D(-30.0f, 0.0f, 0.0f));

    cylinderMesh->setRadius(6.0f);
    cylinderMesh->setLength(38.0f);
    cylinderMesh->setSlices(16);
    cylinderMesh->setRings(32);

    cylEntity->addComponent(cylinderMesh);
    cylEntity->addComponent(cylTransform);
    cylEntity->addComponent(torusMaterial);


    Qt3DCore::QEntity *cylEntity2 = new Qt3DCore::QEntity(resultEntity);

    Qt3DExtras::QCylinderMesh *cylinderMesh2 = new Qt3DExtras::QCylinderMesh(cylEntity2);

    Qt3DCore::QTransform *cylTransform2 = new Qt3DCore::QTransform(resultEntity);
    cylTransform2->setTranslation(QVector3D(-22.5f, 0.0f, 0.0f));
    cylTransform2->setRotationZ(90.0f);

    cylinderMesh2->setRadius(6.0f);
    cylinderMesh2->setLength(15.0f);
    cylinderMesh2->setSlices(16);
    cylinderMesh2->setRings(32);

    cylEntity2->addComponent(cylinderMesh2);
    cylEntity2->addComponent(cylTransform2);
    cylEntity2->addComponent(torusMaterial);


    return resultEntity;

}

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow view;

    Qt3DCore::QEntity *rootEntity = createScene();

    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1f, 1000.0f);

    camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(180.0f);
    cameraController->setLinearSpeed(50.0f);

    view.setRootEntity(rootEntity);

    view.show();

    return app.exec();

}
