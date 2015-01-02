/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * PreviewFileDialog class - extension of QFileDialog class. Added preview display
 *
 * Copyright (C) 2014 Krzysztof Marczak
 *
 * This file is part of Mandelbulber.
 *
 * Mandelbulber is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Mandelbulber is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 */

#include "preview_file_dialog.h"
#include <QGridLayout>
#include "parameters.hpp"
#include "thumbnail.hpp"
#include "settings.hpp"
#include "initparameters.hpp"

PreviewFileDialog::PreviewFileDialog(QWidget *parent) : QFileDialog(parent)
{
	setOption(QFileDialog::DontUseNativeDialog);

	preview = NULL;
	vboxlayout = new QVBoxLayout();

	checkbox = new QCheckBox(tr("Preview"));
	checkbox->setChecked(true);

	preview = new QLabel("", this);
	preview->setAlignment(Qt::AlignCenter);
	preview->setObjectName("label_preview");

	info = new QLabel("");

	progressBar = new QProgressBar(this);
	progressBar->setMaximum(1000);
	progressBar->setAlignment(Qt::AlignCenter);

	vboxlayout->addWidget(checkbox);
	vboxlayout->addWidget(preview);
	vboxlayout->addWidget(info);
	vboxlayout->addWidget(progressBar);
	progressBar->hide();
	vboxlayout -> addStretch();

	//add to existing layout
	QGridLayout *gridlayout = (QGridLayout*)this->layout();
	gridlayout->addLayout(vboxlayout, 1, 3, 3, 1);

	connect(this, SIGNAL(currentChanged(const QString&)), this, SLOT(OnCurrentChanged(const QString&)));

}

PreviewFileDialog::~PreviewFileDialog()
{
	delete vboxlayout;
	delete preview;
	delete info;
	delete progressBar;
}

void PreviewFileDialog::OnCurrentChanged(const QString & filename)
{
	QPixmap pixmap;
	if (QFileInfo(filename).suffix() == QString("fract"))
	{
		cSettings parSettings(cSettings::formatFullText);
		parSettings.BeQuiet(true);
		if (parSettings.LoadFromFile(filename))
		{
			cParameterContainer *par = new cParameterContainer;
			cFractalContainer *parFractal = new cFractalContainer;
			InitParams(par);
			for(int i=0; i<NUMBER_OF_FRACTALS; i++)
				InitFractalParams(&parFractal->at(i));
			if(parSettings.Decode(par, parFractal))
			{
				cThumbnail thumbnail(par, parFractal, 200, 200, parSettings.GetHashCode());
				thumbnail.AssignProgressBar(progressBar);
				progressBar->show();
				pixmap = thumbnail.Render();
				preview->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
				progressBar->hide();
			}
			else
			{
				preview->setText(" ");
				info->setText(" ");
			}
			delete par;
			delete parFractal;
		}
	}
	else
	{
		pixmap.load(filename);
		if(pixmap.isNull() || !checkbox->isChecked())
		{
			preview->setText(" ");
			info->setText(" ");
		}
		else
		{
			preview->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			QString text = QString::number(pixmap.width()) + QString(" x ") + QString::number(pixmap.height());
			info->setText(text);
		}
	}
}

