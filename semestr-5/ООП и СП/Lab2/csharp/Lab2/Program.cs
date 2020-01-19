using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Person
    {
        private string name;
        public static Person first;
        public static Person last;
        Person next;
        public Person()
        {
            next = null;
            if (first == null) first = this;
            if (last != null) last.next = this;
            last = this;

            name = "Vladimir";
        }
        public static void print()
        {
            Person i = first;
            while (i != null)
            {
                i.show();
                i = i.next;
            }
        }
        public virtual void show()
        {
            Console.WriteLine($"Name: {name}");
        }
    }
    class Student : Person
    {
        private string name;
        private int age;
        private int course;
        public Student() : base()
        {
            name = "Viktor";
            age = 22;
            course = 2;
        }
        public override void show()
        {
            Console.Write($"Name: {name}; ");
            Console.Write($"Age: {age}; ");
            Console.WriteLine($"Course: {course}");
        }
    }
    class Teacher : Person
    {
        private string name;
        private int age;
        private int experience;
        public Teacher() : base()
        {
            name = "Olga";
            age = 35;
            experience = 15;
        }
        public override void show()
        {
            Console.Write($"Name: {name}; ");
            Console.Write($"Age: {age}; ");
            Console.WriteLine($"Experience: {experience}");
        }
    }
    class Head : Person
    {
	    private string name;
        private int age;
        private bool secondment;
        public Head() : base()
        {
            name = "Alexey";
            age = 47;
            secondment = true;
        }
        public override void show()
        {
            Console.Write($"Name: {name}; ");
            Console.Write($"Age: {age}; ");
            Console.WriteLine($"Secondment: {secondment}");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Person obj1 = new Person();
            Student obj2 = new Student();
            Teacher obj3 = new Teacher();
            Head obj4 = new Head();
            Head.print();
            Console.ReadKey();
        }
    }
}
