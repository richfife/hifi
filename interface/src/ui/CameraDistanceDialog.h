//
//  cameraDistanceDialog.h
//  interface/src/ui
//
//  Created by Brad Hefta-Gaub on 7/19/13.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_CameraDistanceDialog_h
#define hifi_CameraDistanceDialog_h

#include <QDialog>

class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QSlider;

class CameraDistanceDialog : public QDialog {
    Q_OBJECT
public:
    // Sets up the UI
    CameraDistanceDialog(QWidget* parent);

    void SetDistancePointer(float *_scaleDistance);

signals:
    void closed();

public slots:
    void reject() override;
    void distanceValueChanged(int value);
    void resetClicked(bool checked);
    void reloadSliders();
    void updateDistanceAdjust();

protected:

    // Emits a 'closed' signal when this dialog is closed.
    void closeEvent(QCloseEvent* event) override;

private:
    QSlider* _distance;

    QLabel* _feedback;

    float *_scaleDistance;
};

#endif // hifi_CameraDistanceDialog_h
