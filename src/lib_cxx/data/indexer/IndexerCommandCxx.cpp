#include "data/indexer/IndexerCommandCxx.h"

#include <QJsonArray>
#include <QJsonObject>

#include "utility/utilityString.h"

IndexerCommandCxx::IndexerCommandCxx(
	const FilePath& sourceFilePath,
	const std::set<FilePath>& indexedPaths, 
	const std::set<FilePathFilter>& excludeFilters,
	const std::set<FilePathFilter>& includeFilters,
	const FilePath& workingDirectory,
	const std::vector<FilePath>& systemHeaderSearchPaths,
	const std::vector<FilePath>& frameworkSearchPaths,
	const std::vector<std::wstring>& compilerFlags
)
	: IndexerCommand(sourceFilePath)
	, m_indexedPaths(indexedPaths)
	, m_excludeFilters(excludeFilters)
	, m_includeFilters(includeFilters)
	, m_workingDirectory(workingDirectory)
	, m_systemHeaderSearchPaths(systemHeaderSearchPaths)
	, m_frameworkSearchPaths(frameworkSearchPaths)
	, m_compilerFlags(compilerFlags)
{
}

size_t IndexerCommandCxx::getByteSize(size_t stringSize) const
{
	size_t size = IndexerCommand::getByteSize(stringSize);

	for (const FilePath& path : m_indexedPaths)
	{
		size += stringSize + utility::encodeToUtf8(path.wstr()).size();
	}

	for (const FilePathFilter& filter : m_excludeFilters)
	{
		size += stringSize + utility::encodeToUtf8(filter.wstr()).size();
	}

	for (const FilePathFilter& filter : m_includeFilters)
	{
		size += stringSize + utility::encodeToUtf8(filter.wstr()).size();
	}

	for (const FilePath& path : m_systemHeaderSearchPaths)
	{
		size += stringSize + utility::encodeToUtf8(path.wstr()).size();
	}

	for (const FilePath& path : m_frameworkSearchPaths)
	{
		size += stringSize + utility::encodeToUtf8(path.wstr()).size();
	}

	for (const std::wstring& flag : m_compilerFlags)
	{
		size += stringSize + flag.size();
	}

	return size;
}

const std::set<FilePath>& IndexerCommandCxx::getIndexedPaths() const
{
	return m_indexedPaths;
}

const std::set<FilePathFilter>& IndexerCommandCxx::getExcludeFilters() const
{
	return m_excludeFilters;
}

const std::set<FilePathFilter>& IndexerCommandCxx::getIncludeFilters() const
{
	return m_includeFilters;
}

const std::vector<FilePath>& IndexerCommandCxx::getSystemHeaderSearchPaths() const
{
	return m_systemHeaderSearchPaths;
}

const std::vector<FilePath>& IndexerCommandCxx::getFrameworkSearchPaths() const
{
	return m_frameworkSearchPaths;
}

const std::vector<std::wstring>& IndexerCommandCxx::getCompilerFlags() const
{
	return m_compilerFlags;
}

const FilePath& IndexerCommandCxx::getWorkingDirectory() const
{
	return m_workingDirectory;
}

QJsonObject IndexerCommandCxx::doSerialize() const
{
	QJsonObject jsonObject = IndexerCommand::doSerialize();

	{
		QJsonArray indexedPathsArray;
		for (const FilePath& indexedPath : m_indexedPaths)
		{
			indexedPathsArray.append(QString::fromStdWString(indexedPath.wstr()));
		}
		jsonObject["indexed_paths"] = indexedPathsArray;
	}
	{
		QJsonArray excludeFiltersArray;
		for (const FilePathFilter& excludeFilter : m_excludeFilters)
		{
			excludeFiltersArray.append(QString::fromStdWString(excludeFilter.wstr()));
		}
		jsonObject["exclude_filters"] = excludeFiltersArray;
	}
	{
		QJsonArray includeFiltersArray;
		for (const FilePathFilter& includeFilter : m_includeFilters)
		{
			includeFiltersArray.append(QString::fromStdWString(includeFilter.wstr()));
		}
		jsonObject["include_filters"] = includeFiltersArray;
	}
	{
		jsonObject["working_directory"] = QString::fromStdWString(getWorkingDirectory().wstr());
	}
	{
		QJsonArray systemHeaderSearchPathsArray;
		for (const FilePath& systemHeaderSearchPath : m_systemHeaderSearchPaths)
		{
			systemHeaderSearchPathsArray.append(QString::fromStdWString(systemHeaderSearchPath.wstr()));
		}
		jsonObject["system_header_search_paths"] = systemHeaderSearchPathsArray;
	}
	{
		QJsonArray frameworkSearchPathsArray;
		for (const FilePath& frameworkSearchPath : m_frameworkSearchPaths)
		{
			frameworkSearchPathsArray.append(QString::fromStdWString(frameworkSearchPath.wstr()));
		}
		jsonObject["framework_search_paths"] = frameworkSearchPathsArray;
	}
	{
		QJsonArray compilerFlagsArray;
		for (const std::wstring& compilerFlag : m_compilerFlags)
		{
			compilerFlagsArray.append(QString::fromStdWString(compilerFlag));
		}
		jsonObject["compiler_flags"] = compilerFlagsArray;
	}

	return jsonObject;
}
