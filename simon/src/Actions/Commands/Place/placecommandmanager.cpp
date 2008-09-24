#include "placecommandmanager.h"
#include "../../../SimonLib/Settings/settings.h"
#include "../../../SimonLib/Logging/logger.h"
#include "xmlplacecommand.h"
#include "placecommand.h"
#include <KLocalizedString>

PlaceCommandManager::PlaceCommandManager(QObject *parent) : CommandManager(parent)
{
	this->xmlPlaceCommand = new XMLPlaceCommand();
}

const QString PlaceCommandManager::name() const
{
	return PlaceCommand::staticCategoryText();
}

bool PlaceCommandManager::addCommand(Command *command)
{
	if (dynamic_cast<PlaceCommand*>(command))
	{
		this->commands->append(command);
		return save();
	}
	return false;
}

bool PlaceCommandManager::load()
{
	QString commandPath = Settings::getS("Commands/Place/PathToConfig");
	Logger::log(i18n("[INF] Lade Ort-Kommandos von %1", commandPath));

	bool ok = false;
	this->commands = xmlPlaceCommand->load(ok, commandPath);
	return ok;
}

bool PlaceCommandManager::save()
{
	QString commandPath = Settings::getS("Commands/Place/PathToConfig");
	Logger::log(i18n("[INF] Speichere Ort-Kommandos nach %1", commandPath));
	return xmlPlaceCommand->save(commands, commandPath);
}

PlaceCommandManager::~PlaceCommandManager() 
{
	if (xmlPlaceCommand) xmlPlaceCommand->deleteLater();
}