using System;

namespace Lab3
{
    class List
    {
        const int maxsize = 50;
        private char[] first;
        private int max;
        private int size;
        public List()
        {
            size = 0;
            max = maxsize;
            first = null;
        }
        public List(int value)
        {
            if (value > maxsize) value = maxsize;
            size = value;
            max = maxsize;
            first = new char[size + 1];
            init(first, size);
        }
        public List(List obj)
        {
            size = obj.size;
            max = obj.max;
            first = new char[size + 1];
            init(first, size);
            for (int i = 0; i < size; i++)
                first[i] = obj.first[i];
        }
        ~List()
        {
            first = null;
        }
        public void input()
        {
            char value;
            value = char.Parse(Console.ReadLine());
            add(value);
        }
        public void output()
        {
            for (int i = 0; i < size; i++)
            {
                Console.Write(first[i]);
            }
            Console.WriteLine();
        }
        private void init(char[] arr, int size)//инициализация данных массива
        {
            for (int i = 0; i < size + 1; i++)
            {
                arr[i] = '\0';
            }
        }
        private void add(char item)//добавление элемента в новый большего размера массив
        {
            if (resize(size + 1, true))
                first[size - 1] = item;
        }
        private bool resize(int value, bool savedata)
        {
            if (value > max) return false;
            char[] tmp = new char[value + 1];
            init(tmp, value);
            if (savedata)
            {
                for (int i = 0; i < value - 1; i++)
                    tmp[i] = first[i];
            }
            first = tmp;
            size = value;
            return true;
        }
        public static List operator +(char left, List right)
        {
	        List tmp = new List(right.size + 1);
	        for (int i = 0; i<right.size; i++)
		        tmp.first[i] = right.first[i];
	        tmp.first[right.size] = left;
	        return tmp;
        }
        public static List operator +(List left, List right)
        {
            List tmp = new List(left.size +right.size);
            int oldsize = left.size;
            for (int i = 0; i<oldsize; i++)
                tmp.first[i] = left.first[i];
            for (int i = oldsize; i<tmp.size; i++)
                tmp.first[i] = right.first[i - oldsize];
            return tmp;
        }
        public static bool operator ==(List left, List right)
        {
            if (left.size != right.size) return false;
            for (int i = 0; i<left.size; i++)
                if (left.first[i] != right.first[i]) return false;
            return true;
        }
        public static bool operator !=(List left, List right)
        {
            if (left.size != right.size) return true;
            for (int i = 0; i < left.size; i++)
                if (left.first[i] != right.first[i]) return true;
            return false;
        }
        public override bool Equals(object o)
        {
            return true;
        }
        public override int GetHashCode()
        {
            return 0;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            List obj1 = new List();
            for (int i = 0; i < 3; i++)
                obj1.input();
            obj1.output();

            List obj2 = new List();
            obj2 = obj1;
            List obj3 = new List();
            obj3 = obj1 + obj2;
            obj3.output();
            obj3 = 'f' + obj2;
            obj3.output();
            if (obj1 == obj2) Console.WriteLine("obj1 == ob2");
        }
    }
}
