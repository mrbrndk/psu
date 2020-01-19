using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Car
    {
        private string name;
        private string model;
        private string color;
        int weight;
        int maxspeed;
        int year;
        public Car()
        {
            Console.WriteLine("constructor without param");
            name = "Unknown";
            model = "Unknown";
            color = "Unknown";
            weight = 0;
            maxspeed = 0;
            year = 1767;
        }
        public Car(string newname, string newmodel, string newcolor, int newweight, int newmaxspeed, int newyear)
        {
            Console.WriteLine("constructor with param");
            name = newname;
            model = newmodel;
            color = newcolor;
            weight = newweight;
            maxspeed = newmaxspeed;
            year = newyear;
        }
        ~Car()
        {
            Console.WriteLine("destructor");
        }
        public void GetCar()
        {
            Console.WriteLine("<< OUTPUT <<");
            Console.WriteLine($"NAME: {name}");
            Console.WriteLine($"MODEL: {model}");
            Console.WriteLine($"COLOR: {color}");
            Console.WriteLine($"WEIGHT: {weight}");
            Console.WriteLine($"MAXSPEED: {maxspeed}");
            Console.WriteLine($"YEAR: {year}");
        }
        public void SetCar()
        {
            Console.WriteLine(">> INPUT >>");
            Console.Write("NAME: ");
            name = Console.ReadLine();
            Console.Write("MODEL: ");
            model = Console.ReadLine();
            Console.Write("COLOR: ");
            color = Console.ReadLine();
            Console.Write("WEIGHT: ");
            weight = int.Parse(Console.ReadLine());
            Console.Write("MAXSPEED: ");
            maxspeed = int.Parse(Console.ReadLine());
            Console.Write("YEAR: ");
            year = int.Parse(Console.ReadLine());
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Car obj1 = new Car();
            obj1.GetCar();
            obj1.SetCar();
            Car obj2 = new Car("Tesla", "X", "Black", 3000, 300, 2017);
            obj2.GetCar();
            Console.ReadKey();
        }
    }
}
