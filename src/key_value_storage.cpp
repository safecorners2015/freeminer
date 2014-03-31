/*
  This file is part of Freeminer.

  Freeminer is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Freeminer  is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Freeminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "exceptions.h"
#include "filesys.h"
#include "key_value_storage.h"

KeyValueStorage::KeyValueStorage(const std::string &savedir) throw(KeyValueStorageException)
	:
	m_savedir(savedir),
	m_db_name("key_value_storage")
{
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, savedir + DIR_DELIM +  m_db_name + ".db", &m_db);
	if(!status.ok()) {
		throw KeyValueStorageException(status.ToString());
	}
}

void KeyValueStorage::put(const char *key, const char *data) throw(KeyValueStorageException)
{
	leveldb::WriteOptions write_options;
	leveldb::Status status = m_db->Put(write_options, key, data);
	if(!status.ok()) {
		throw KeyValueStorageException(status.ToString());
	}
}

void KeyValueStorage::get(const char *key, std::string &data) throw(KeyValueStorageException)
{
	leveldb::ReadOptions read_options;
	leveldb::Status status = m_db->Get(read_options, key, &data);
	if(!status.ok()) {
		throw KeyValueStorageException(status.ToString());
	}
}

void KeyValueStorage::del(const char *key) throw(KeyValueStorageException)
{
	leveldb::WriteOptions write_options;
	leveldb::Status status = m_db->Delete(write_options, key);
	if(!status.ok()) {
		throw KeyValueStorageException(status.ToString());
	}
}

