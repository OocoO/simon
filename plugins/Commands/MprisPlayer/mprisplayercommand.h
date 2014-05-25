/*
 *   Copyright (C) 2014 Ashish Madeti <ashishmadeti@gmail.com>
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

#ifndef SIMON_MPRISPLAYERCOMMAND_H_1822E03B797C494599B9629C6B47E478
#define SIMON_MPRISPLAYERCOMMAND_H_1822E03B797C494599B9629C6B47E478

#include <simonscenarios/command.h>

#include <QDomElement>
#include <QDomDocument>

/**
 *	@class MprisPlayerCommand
 *	@brief Ressembles one exec-command
 *
 *	@version 0.1
 *	@date 19.05.2014
 *	@author Ashish Madeti
 */
class MprisPlayerCommand : public Command
{
  public:
    static const QString staticCategoryText();
    static const KIcon staticCategoryIcon();

    const QString getCategoryText() const;
    const KIcon getCategoryIcon() const;

    QDomElement serializePrivate(QDomDocument *doc, QDomElement& commandElem);
    bool deSerializePrivate(const QDomElement& commandElem);

    MprisPlayerCommand(const QString& name, const QString& iconSrc, const QString& description,
                const QString& serviceName, const QString& path, const QString& interface,
                const QString& method, const QStringList& args) :
        Command(name, iconSrc, description),
        m_serviceName(serviceName), m_path(path),
        m_interface(interface),
        m_method(method), m_args(args)
    {
    }
    ~MprisPlayerCommand() {}

    QString serviceName();
    QString path();
    QString interface();
    QString method();
    QStringList arguments();

    STATIC_CREATE_INSTANCE_H(MprisPlayerCommand)

  protected:
    const QMap<QString,QVariant> getValueMapPrivate() const;
    bool triggerPrivate(int *state);
    MprisPlayerCommand() {}

  private:
    QString m_serviceName;
    QString m_path;
    QString m_interface;
    QString m_method;
    QStringList m_args;
};

#endif // SIMON_MPRISPLAYERCOMMAND_H_1822E03B797C494599B9629C6B47E478
