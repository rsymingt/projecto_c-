
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

	public:

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
