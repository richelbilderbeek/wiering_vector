#define UNSIGNED_SHORT_INT_BOUNDARY 65535
#define STARTING_SIZE 8
template <class T> class Vector
{
	public:
		Vector(unsigned short int i = STARTING_SIZE)
		{
			if(i > 0) { TArray = new T[i]; array_size = i; }
			else { TArray = new T[STARTING_SIZE]; array_size = STARTING_SIZE; }
			user_given_size = array_size;
		}
		
		~Vector() { delete[]  TArray; TArray = NULL; }
		
		bool equals(Vector v)
		{
			if(this->sp != v.sp) { return false; }
			for(unsigned short int i = 0; i < sp; i++)
			{ if(this->TArray[i] != v.TArray[i]) { return false; } }
			return true;
		}
		
		void CopyOf(Vector v)
		{
			sp = v.sp;
			array_size = v.array_size;
			TArray = new T[array_size];
			for(unsigned short int i = 0; i < sp; i++) { TArray[i] = v.TArray[i]; }
		}
		
		bool push_unique(T x)
		{
			for(unsigned short int i = 0; i < sp; i++) { if(x == TArray[i]) { return false; } }
			push(x); return true;
		}
		
		bool add_unique(T x)
		{
			for(unsigned short int i = 0; i < sp; i++) { if(x == TArray[i]) { return false; } }
			add(x); return true;
		}
		
		bool insert_unique(T x)
		{
			for(unsigned short int i = 0; i < sp; i++) { if(x == TArray[i]) { return false; } }
			insert(x); return true;
		}
		
		void insert(T x)
		{
			if(sp >= array_size) { DoubleArraySize(); };
			for(unsigned short int i = sp; i > 0; i--) { TArray[i] = TArray[i-1]; }
			TArray[0] = x;
			sp++;
		}
		
		void push(T x)
		{
			if(sp >= array_size) { DoubleArraySize(); }
			TArray[sp] = x;
			sp++;
		}
		
		void add(T x)
		{
			if(sp >= array_size) { DoubleArraySize(); }
			TArray[sp] = x;
			sp++;
		}
		
		bool contains(T x)
		{ for(unsigned short int i = 0; i < sp; i++) { if(x == TArray[i]) { return true; } } return false; }
		
		unsigned short int count(T x)
		{
			unsigned short int counter = 0;
			for(unsigned short int i = 0; i < sp; i++) { if(x == TArray[i]) { counter++; } }
			return counter;
		}
		
		unsigned short int search(T x)
		{
			for(unsigned short int i = 0; i < sp; i++)
			{ if(x == TArray[i]) { return i; } }
			return sp;
		}
		
		void remove(unsigned short int i)
		{
			if( i >= sp ) { return; }
			for(unsigned short int j = i+1; j < sp; j++) { TArray[j-1] = TArray[j]; }
			sp--;
		}
		
		void removeRange(unsigned short int a, unsigned short int b)
		{
			if(a > b || b >= sp) { return; }
			int range = b - a + 1;
			for(unsigned short int j = a+range; j < sp; j++) { TArray[j-range] = TArray[j]; }
			sp -= range;
		}
		
		unsigned short int replaceAll(T x, T y)
		{
			unsigned short int replaced = 0;
			for(unsigned short int i = sp - 1; i < UNSIGNED_SHORT_INT_BOUNDARY; i--)
			{ if(x == TArray[i]) { set(i,y); replaced++; } }
			return replaced;
		}
		
		unsigned short int removeAll(T x)
		{
			unsigned short int removed = 0;
			for(unsigned short int i = sp - 1; i < UNSIGNED_SHORT_INT_BOUNDARY; i--)
			{ if(x == TArray[i]) { remove(i); removed++; } }
			return removed;
		}
		
		void wissel(unsigned short int a, unsigned short int b)
		{ T x = index(a); T y = index(b);  set(b, x); set(a, y); }
		
		bool empty() { if(sp == 0) { return true; } else { return false; } }
		bool isEmpty() { if(sp == 0) { return true; } else { return false; } }
		void clear() { sp = 0; }
		void deep_clear() { sp = 0; trim(); }
		unsigned short int size() { return sp; }
		unsigned short int length() { return sp; }
		unsigned short int real_size() { return array_size; }
		unsigned short int real_length() { return array_size; }
		
		bool mod(unsigned short int i, T x) { if(i < sp) { TArray[i] = x; return true;} return false; }
		bool set(unsigned short int i, T x) { if(i < sp) { TArray[i] = x; return true;} return false; }
		
		bool trim()
		{
			if(sp != array_size && !(sp == 0 && array_size == 1)) { SetToSize(sp); return true; } else { return false; }
		}
		
		bool resize(unsigned short int i)
		{ if(i >= sp && i != array_size) { SetToSize(i); return true; } else { return false; } }
		
		T index(unsigned short int i) { if(i < sp) { return TArray[i]; } return TArray[0]; }
		T get(unsigned short int i) { if(i < sp) { return TArray[i]; }  return TArray[0]; }
		
		T pop() { if(sp >= 1) { sp--; return TArray[sp]; } else { return TArray[0]; } }
		T top() { if(sp >= 1) { return TArray[sp-1]; } else { return TArray[0]; } }
		
		void stats()
		{
			std::cout << "stack pointer: " << sp << std::endl;
			std::cout << "real array size: " << array_size << std::endl;
			std::cout << "user given size: " << user_given_size << std::endl << std::endl;
		}
		
		void show_all()
		{
			for(unsigned short int i = 0; i < sp; i++)
			{
				std::cout << i+1 << ") " << TArray[i] << std::endl;
			}
		}
		
	private:
	
		void SetToSize(unsigned short int new_size)
		{
			if(new_size == 0) { new_size = 1; }
			T *temp = new T[array_size];
			for(unsigned short int i = 0; i < array_size; i++) { temp[i] = TArray[i];}
			delete[] TArray; TArray = NULL; TArray = new T[new_size];
			int t = (array_size > new_size ? new_size : array_size);
			if(t > sp) { t = sp; }
			for(unsigned short int i = 0; i < t; i++)
			{ TArray[i] = temp[i]; }
			delete[] temp; temp = NULL; array_size = new_size;
		}
	
		void DoubleArraySize()
		{
			T *temp = new T[array_size];
			for(unsigned short int i = 0; i < array_size; i++) { temp[i] = TArray[i];}
			delete[] TArray; TArray = NULL; array_size *= 2;
			TArray = new T[array_size];
			for(unsigned short int i = 0; i < array_size / 2; i++) { TArray[i] = temp[i]; }
			delete[] temp; temp = NULL;
		}
	
		unsigned short int user_given_size = 0;
		unsigned short int array_size = 0;
		unsigned short int sp = 0;
		T *TArray = new T[STARTING_SIZE];
};
