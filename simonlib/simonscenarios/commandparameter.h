/*
 *   Copyright (C) 2011 Peter Grasch <peter.grasch@bedahr.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SIMON_COMMANDPARAMETER_H_651AF6CF619F4C8EA4E38A3F99962A60
#define SIMON_COMMANDPARAMETER_H_651AF6CF619F4C8EA4E38A3F99962A60

#include <QString>

class CommandParameter
{
  private:
    QString m_name;
    bool m_optional;

  public:
    explicit CommandParameter(const QString& name, bool optional=false);
    QString name() { return m_name; }
    bool optional() { return m_optional; }

};

#endif
