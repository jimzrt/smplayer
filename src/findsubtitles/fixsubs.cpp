/*  smplayer, GUI front-end for mplayer.
    Copyright (C) 2006-2025 Ricardo Villalba <ricardo@smplayer.info>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "fixsubs.h"
#include <QFile>

FixSubtitles::ErrorCode FixSubtitles::fix(const QString & in_file, const QString & out_file) {
	QFile file(in_file);
	QByteArray result;

	if (!file.open(QIODevice::ReadOnly)) {
		return ReadError;
	}

	while (!file.atEnd()) {
		QByteArray line = file.readLine().replace("\r\n", "\n").replace("\r", "\n").replace("\n", "\r\n");
		//qDebug("l: '%s'", line.constData());
		result += line;
	}
	file.close();
	//qDebug("r: '%s'", result.constData());

	QString out = out_file;
	if (out.isEmpty()) out = in_file;
	file.setFileName(out);

	if (!file.open(QIODevice::WriteOnly)) {
		return WriteError;
	}

	file.write(result);
	file.close();

	return NoError;
}

