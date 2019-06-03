#include "FileSorts.h"

#include "utils/StringUtil.h"

namespace FileSorts
{
	const FileData::SortType typesArr[] = {
		FileData::SortType(&compareName, true, "filename, ascending"),
		FileData::SortType(&compareName, false, "filename, descending"),

		FileData::SortType(&compareRating, true, "rating, ascending"),
		FileData::SortType(&compareRating, false, "rating, descending"),

		FileData::SortType(&compareTimesPlayed, true, "times played, ascending"),
		FileData::SortType(&compareTimesPlayed, false, "times played, descending"),

		FileData::SortType(&compareLastPlayed, true, "last played, ascending"),
		FileData::SortType(&compareLastPlayed, false, "last played, descending"),

		FileData::SortType(&compareNumPlayers, true, "number of players, ascending"),
		FileData::SortType(&compareNumPlayers, false, "number of players, descending"),

		FileData::SortType(&compareReleaseDate, true, "release date, ascending"),
		FileData::SortType(&compareReleaseDate, false, "release date, descending"),

		FileData::SortType(&compareGenre, true, "genre, ascending"),
		FileData::SortType(&compareGenre, false, "genre, descending"),

		FileData::SortType(&compareDeveloper, true, "developer, ascending"),
		FileData::SortType(&compareDeveloper, false, "developer, descending"),

		FileData::SortType(&comparePublisher, true, "publisher, ascending"),
		FileData::SortType(&comparePublisher, false, "publisher, descending"),

		FileData::SortType(&compareSystem, true, "system, ascending"),
		FileData::SortType(&compareSystem, false, "system, descending")
	};

	const std::vector<FileData::SortType> SortTypes(typesArr, typesArr + sizeof(typesArr)/sizeof(typesArr[0]));

	//returns if file1 should come before file2
	bool compareName(const FileData* file1, const FileData* file2)
	{
		std::string name1 = file1->metadata.getSortName();
		return name1.compare(file2->metadata.getSortName()) < 0;	
	}

	bool compareRating(const FileData* file1, const FileData* file2)
	{
		return file1->metadata.getFloat("rating") < file2->metadata.getFloat("rating");
	}

	bool compareTimesPlayed(const FileData* file1, const FileData* file2)
	{
		//only games have playcount metadata
		if(file1->metadata.getType() == GAME_METADATA && file2->metadata.getType() == GAME_METADATA)
		{
			return (file1)->metadata.getInt("playcount") < (file2)->metadata.getInt("playcount");
		}

		return false;
	}

	bool compareLastPlayed(const FileData* file1, const FileData* file2)
	{
		// since it's stored as an ISO string (YYYYMMDDTHHMMSS), we can compare as a string
		// as it's a lot faster than the time casts and then time comparisons
		return (file1)->metadata.get("lastplayed") < (file2)->metadata.get("lastplayed");
	}

	bool compareNumPlayers(const FileData* file1, const FileData* file2)
	{
		return (file1)->metadata.getInt("players") < (file2)->metadata.getInt("players");
	}

	bool compareReleaseDate(const FileData* file1, const FileData* file2)
	{
		// since it's stored as an ISO string (YYYYMMDDTHHMMSS), we can compare as a string
		// as it's a lot faster than the time casts and then time comparisons
		return (file1)->metadata.get("releasedate") < (file2)->metadata.get("releasedate");
	}

	bool compareGenre(const FileData* file1, const FileData* file2)
	{
		std::string genre1 = Utils::String::toUpper(file1->metadata.get("genre"));
		std::string genre2 = Utils::String::toUpper(file2->metadata.get("genre"));
		return genre1.compare(genre2) < 0;
	}

	bool compareDeveloper(const FileData* file1, const FileData* file2)
	{
		std::string developer1 = Utils::String::toUpper(file1->metadata.get("developer"));
		std::string developer2 = Utils::String::toUpper(file2->metadata.get("developer"));
		return developer1.compare(developer2) < 0;
	}

	bool comparePublisher(const FileData* file1, const FileData* file2)
	{
		std::string publisher1 = Utils::String::toUpper(file1->metadata.get("publisher"));
		std::string publisher2 = Utils::String::toUpper(file2->metadata.get("publisher"));
		return publisher1.compare(publisher2) < 0;
	}

	bool compareSystem(const FileData* file1, const FileData* file2)
	{
		std::string system1 = Utils::String::toUpper(file1->getSystemName());
		std::string system2 = Utils::String::toUpper(file2->getSystemName());
		return system1.compare(system2) < 0;
	}
};
