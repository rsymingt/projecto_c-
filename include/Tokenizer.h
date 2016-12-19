
using std::string;

class Tokenizer
{

	private:
		string str;
		char delimiter;
		string strDelimiter;

	public:
		string getNext()
		{
			string tok;

			if(str.find(delimiter) != -1)
			{
				int i = str.find(delimiter);
				tok = str.substr(0, i);
				str = str.substr(i);
			}
			else
			{
				tok = str;
				str = "";
			}

			if(str[0] == delimiter)
			{
				int i = 0;
				for(; i < str.size() && str[i] == delimiter; i ++);

				str = str.substr(i);
			}

			return tok;
		}

		bool hasNext()
		{
			if(str.find(delimiter) == -1 && str.size() == 0)
				return false;
			return true;
		}

		string getString()
		{
			return str;
		}

		char getDelimiter()
		{
			return delimiter;
		}

		void setString(string str)
		{
			this->str = str;
		}

		void setDelimiter(string str)
		{
			this->str = str;
		}

		Tokenizer(string str, char delimiter)
		{
			this->str = str;
			this->delimiter = delimiter;
		}

		Tokenizer(char delimiter)
		{
			this->delimiter = delimiter;
		}

		~Tokenizer()
		{
		}
};
