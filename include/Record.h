

class Record
{
	private:
		Record *next;
		string txt;

	public:

		void settxt(string txt)
		{
			this->txt = txt;
		}

		string getText()
		{
			return txt;
		}

		Record * getNext()
		{
			return next;
		}

		Record(string txt)
		{
			next = NULL;
			this->txt = txt;
		}

		~Record()
		{

		}

		friend class LinkedList;
};
