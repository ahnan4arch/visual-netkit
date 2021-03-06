/**
 * VisualNetkit is an advanced graphical tool for NetKit <http://www.netkit.org>
 * Copyright (C) 2008  Alessio Di Fazio, Paolo Minasi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FILEEDITOR_H_
#define FILEEDITOR_H_

#include <QWidget>
#include <QDebug>

#include "SyntaxHighLighter.h"

#include "ui_fileEdit.h"

/**
 * This widget is a file editor showed inside the main tab widget
 */
class FileEditor : public QWidget, public Ui::FileEditWidget
{
	Q_OBJECT

private:
	SyntaxHighLighter *highlighter;
	bool contentChanged;
	QString newContent;

public:
	FileEditor(QString &fileContent, QWidget *parent = 0);
	virtual ~FileEditor();
	bool textHasChanged() { return saveButton->isEnabled(); };
	bool needBackup() { return (backupCheckBox->checkState() == Qt::Checked); };
	void setFileContentChanged(QString content);

private slots:
	void changeWrapMode(int state);
	void saveChangedDocument();
	void markModified();
	void undoIsAvailable(bool state);
	void wakeUpForChanges();

};

#endif /*FILEEDITOR_H_*/
