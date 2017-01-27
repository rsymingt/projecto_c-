
#include "Record.h"

class LinkedList
{
	private:
		Record *record;

		bool insert(Record *&record, string txt)
		{
			if(record == NULL)
			{
				record = new Record(txt);

				return true;
			}
			else if(record->txt.compare(txt) == 0)
			{
				return false;
			}
			else
			{
				insert(record->next, txt);
			}
		}

		void print(Record *&record)
		{
			if(record == NULL)
			{
				return;
			}
			else
			{
				std::cout << record->txt << std::endl;
				print(record->next);
			}
		}

		void destroy(Record *&record)
		{
			if(record == NULL)
			{
				return;
			}
			else
			{
				destroy(record->next);

				delete record;
				record = NULL;
			}
		}

		void clone(Record *&record, LinkedList *&newList)
		{
			if(!record)
			{
				return;
			}
			else
			{
				newList->insert(record->txt);
				clone(record->next, newList);
			}
		}

		bool remove(Record *&record, string txt)
		{
			if(!record)
			{
				return false;
			}
			else
			{
				if(record->txt.compare(txt) == 0)
				{
					Record *next = record->next;
					delete record;
					record = NULL;
					record = next;
					return true;
				}
				return remove(record->next, txt);
			}
		}

	public:

		LinkedList * clone()
		{
			LinkedList *newList = new LinkedList();
			clone(record, newList);

			return newList;
		}

		Record * getRecord()
		{
			return record;
		}

		bool remove(string txt)
		{
			return remove(record, txt);
		}

		bool insert(string txt)
		{
			return insert(record, txt);
		}

		void print()
		{
			print(record);
		}

		LinkedList()
		{
			record = NULL;
		}

		~LinkedList()
		{
			destroy(record);
		}
};
