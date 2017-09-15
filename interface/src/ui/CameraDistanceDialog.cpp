//
//  LodToolsDialog.cpp
//  interface/src/ui
//
//  Created by Brad Hefta-Gaub on 7/19/13.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <QCheckBox>
#include <QColor>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QSlider>
#include <QString>

#include "Menu.h"
#include "ui/CameraDistanceDialog.h"


CameraDistanceDialog::CameraDistanceDialog(QWidget* parent) :
    QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint) 
{
    this->setWindowTitle("Camera Distance");
    // Create layouter
    QFormLayout* form = new QFormLayout(this);

    // Create a label with feedback...
    _feedback = new QLabel(this);
    QPalette palette = _feedback->palette();
    const unsigned redish  = 0xfff00000;
    palette.setColor(QPalette::WindowText, QColor::fromRgb(redish));
    _feedback->setPalette(palette);
    _feedback->setText("Camera distance controller");
    const int FEEDBACK_WIDTH = 350;
    _feedback->setFixedWidth(FEEDBACK_WIDTH);
    form->addRow("You can see... ", _feedback);
    
    _distance = new QSlider(Qt::Horizontal, this);
    const int MAX_DISTANCE = 1000;
    const int MIN_DISTANCE = 2;
    const int STEP_LOD_SIZE = 1;
    const int PAGE_STEP_LOD_SIZE = 100;
    const int SLIDER_WIDTH = 300;
    _distance->setMaximum(MAX_DISTANCE);
    _distance->setMinimum(MIN_DISTANCE);
    _distance->setSingleStep(STEP_LOD_SIZE);
    _distance->setTickInterval(PAGE_STEP_LOD_SIZE);
    _distance->setTickPosition(QSlider::TicksBelow);
    _distance->setFixedWidth(SLIDER_WIDTH);
    _distance->setPageStep(PAGE_STEP_LOD_SIZE);
    int sliderValue = 100;
    _distance->setValue(sliderValue);
    form->addRow("Camera Distance:", _distance);
    connect(_distance,SIGNAL(valueChanged(int)),this,SLOT(distanceValueChanged(int)));

    _scaleDistance = NULL;
    
    // Add a button to reset
    QPushButton* resetButton = new QPushButton("Reset", this);
    form->addRow("", resetButton);
    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetClicked(bool)));

    this->QDialog::setLayout(form);
    
    updateDistanceAdjust();
}

void CameraDistanceDialog::SetDistancePointer(float *scaleDistance)

{
    _scaleDistance = scaleDistance;

}

void CameraDistanceDialog::reloadSliders() {
}

void CameraDistanceDialog::updateDistanceAdjust() {
}

void CameraDistanceDialog::distanceValueChanged(int value) {

    if(_scaleDistance)
        *_scaleDistance = static_cast<float>(value) / 10.0f;
}

void CameraDistanceDialog::resetClicked(bool checked) {

}

void CameraDistanceDialog::reject() {
    // Just regularly close upon ESC
    this->QDialog::close();
}

void CameraDistanceDialog::closeEvent(QCloseEvent* event) {
    this->QDialog::closeEvent(event);
    emit closed();
}


