
//Function to set my id to MST username
void get_identity(std::string &my_id)
{
  my_id = "hdpg4c";
}

//Function to make it easier on you (rather than use void pointers or crazy new C++ templating)
// we'll only test with std::string keys (remember values can be any type)
template <typename K, typename V>
int MyUnorderedMap<K, V>::hash(const K &key) const
{
  int sum = 0;
  for(int i = 0; key[i] != '\0'; i++)
    sum += (int)key[i];

  return sum%reserved_size;
}

//Constructor
template <typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap()
{
  //default array to nullptr
  data_size = 0;
  reserved_size = 0;
  m_data = nullptr;
}

//Destructor Function
template <typename K, typename V>
MyUnorderedMap<K, V>::~MyUnorderedMap()
{
  delete[] m_data;
}

//Copy Constructor
template <typename K, typename V>
MyUnorderedMap<K, V>::MyUnorderedMap(const MyUnorderedMap<K, V> &source)
{
  //sets the source capacity to reserved_size
  //sets the data_size to source size
  reserved_size = source.reserved_size;
  data_size = source.data_size;

  m_data = new MyPair<K, V>[reserved_size];

  for(int i = 0; i < reserved_size; i++)
    m_data[i] = source.m_data[i];
}

//deep copy
template <typename K, typename V>
MyUnorderedMap<K, V> & MyUnorderedMap<K, V>::operator=(const MyUnorderedMap<K, V> &source)
{
  clear(); //calls the clear function

  //sets reserved_size to source reserved_size
  //sets data_size to source data_size

  reserved_size = source.reserved_size;
  data_size = source.data_size;

  delete[] m_data;

  m_data = new MyPair<K, V>[reserved_size];

  //iterates for each reserved_size and
  //sets data arrray to source data
  for (int i = 0; i < reserved_size; i++)
    m_data[i] = source.m_data[i];

  return *this;
}

//Returns the element stored at the index by reference and
//throw an std::out_of_range exception when out-of-bounds
template <typename K, typename V>
V & MyUnorderedMap<K, V>::at(const K &key)
{
  MyPair<K, V> *array = find(key);

  if(array == nullptr)
  {
    throw std::out_of_range("Key is not found! \n");
  }

  return (array->second);
}

//deep copy
template <typename K, typename V>
V & MyUnorderedMap<K, V>::operator[](const K &key)
{
  MyPair<K, V>* array = find(key);
  if (array == nullptr)
  {
    insert(MyPair<K, V>(key));
    return ((find(key))->second);
  }
  else
  {
    return array->second;
  }
}

//Function to empty the HT
template <typename K, typename V>
bool MyUnorderedMap<K, V>::empty() const
{
  return data_size == 0;
}

//Function returns the size of the actual data stored in the array list
template <typename K, typename V>
int MyUnorderedMap<K, V>::size() const
{
  return data_size;
}

//Function clears the Hash table
template <typename K, typename V>
void MyUnorderedMap<K, V>::clear()
{
  //current size and storage is set back to 0
  data_size = 0;
  reserved_size = 0;

  delete[] m_data; //deallocate the elements in m_data array
  m_data = nullptr;  //m_data is set to null pointer
}

//Function inserts the value
template <typename K, typename V>
void MyUnorderedMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
  int size = 20;

  if(reserved_size == 0)
  {
    reserve(size);
  }

  if(data_size ==  reserved_size*(0.6))
  {
    reserve(2 * reserved_size);
  }

  if(data_size == reserved_size*(0.1))
  {
    reserve(reserved_size*0.3);
  }

  K empty = "Empty";
  int pos = hash(init_pair.first);
  int temp = pos;

  for(int i =1;(empty != m_data[pos].first) && (init_pair.first != m_data[pos].first);i++)
  {
    pos = (temp + i)%reserved_size;
  }

  data_size++;

  m_data[pos] = init_pair;
}

//Function removes the elements at index
template <typename K, typename V>
void MyUnorderedMap<K, V>::erase(const K &key)
{
  if(reserved_size > 0)
  {
    int pos = hash(key);
    int temp = pos;
    std::string empty = "Empty";

    for(int i = 1; (m_data[temp].first != key) && (m_data[temp].first != empty);i++)
    {
      temp = (pos + i)%reserved_size;
    }

    m_data[temp] = empty;
  }
  if(data_size == reserved_size*(0.1))
  {
    reserve(reserved_size*0.3);
  }
}

//Function to find a key
template <typename K, typename V>
MyPair<K, V> * MyUnorderedMap<K, V>::find(const K &key) const
{
  if(reserved_size == 0) //if size is zero
    return nullptr; //return null

  int pos = hash(key);
  int temp = pos;

  for(int i = 1;m_data[pos].first != key && m_data[pos].first != "Empty"; i++)
  {
    pos = (temp + i) % reserved_size;
  }

  if(m_data[pos].first == key)
  {
    return &m_data[pos];
  }
  else
    return nullptr;
}

//Function to print the results
template <typename K, typename V>
void MyUnorderedMap<K, V>::print() const
{
  cout<<"(";

  std::string empty_string = "Empty";
  for(int i =0;i<reserved_size;i++)
  {
    if(m_data[i].first != empty_string)
    {
      cout<<"["<<m_data[i].first<<"]"<<"="<<m_data[i].second << endl;
    }
  }
  cout << ")" << endl;
  cout << '\n' << endl;
}

//Function to count
template <typename K, typename V>
int MyUnorderedMap<K, V>::count(const K &key) const
{
  MyPair<K, V> *temp = find(key);
  if(temp == nullptr)
    return false;

  return true;
}

//Function Grows or shrinks reserved_size and size of dynamic array
//to be new_cap large
template <typename K, typename V>
void MyUnorderedMap<K,V>::reserve(int new_cap)
{
  MyPair<K, V> *temp = new MyPair<K, V>[new_cap];
  int size = reserved_size;
  reserved_size = new_cap;

  K Empty = "Empty";

  for(int i = 0; i < new_cap; i++)
  {
    temp[i].first = Empty;
  }

  for(int i = 0; i < size; i++)
  {
    int new_hash = hash(m_data[i].first);
    int array = new_hash;
    int pos = new_hash;

    for(int j = 1; (temp[pos].first != m_data[i].first) && (temp[pos].first != Empty);j++)
    {
      pos = (j + array) % reserved_size;
    }
    temp[pos] = m_data[i];
  }
  delete[] m_data;
  m_data = temp;
}

//Function to count the number of occurances for every word containing
//the word "Virus"
void get_virus_frequency(MyUnorderedMap<std::string, int> &in_tree)
{
  std::string input;
  char Char;
  std::string Word = "";

  while(std::cin>>input)
  {
    input.append(" ");

    for(int i = 0 ; i < input.size() ; i++)
    {
      Char = input[i];
      if((Char >= 'a' && Char <= 'z') || (Char >= 'A' && Char <= 'Z') || Char == '_')
        Word += Char;

      else
      {
        std::string temp = "";

        //upper case and lower case are same
        for(int j = 0 ; j < Word.length() ; j++)
        {
          if(Word[j] == 'V' || Word[j] == 'v' || Word[j] == '_')
            temp += 'v';
          if(Word[j + 1] == 'I' || Word[j + 1] == 'i' || Word[j + 1] == '_')
            temp += 'i';
          if(Word[j + 2] == 'R' || Word[j + 2] == 'r' || Word[j + 2] == '_')
            temp += 'r';
          if(Word[j + 3] == 'U' || Word[j + 3] == 'u' || Word[j + 3] == '_')
            temp += 'u';
          if(Word[j + 4] == 'S' || Word[j + 4] == 's' || Word[j + 4] == '_')
            temp += 's';
        }

        if(temp == "virus") //if the temp is word virus
        {
          if(!in_tree.find(Word)) //if not found then
            in_tree.insert(MyPair<std::string, int>(Word, 1)); //insert
          else
            in_tree[Word]++; //increments the word
        }

        temp = ""; //sets the temp back
        Word = ""; //sets the word back
      }
    }
  }

  return;
}
