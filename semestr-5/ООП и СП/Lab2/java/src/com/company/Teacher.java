package com.company;

public class Teacher extends Person {
    private String name;
    private int age;
    private int experience;
    public Teacher()
    {
        super();
        name = "Olga";
        age = 35;
        experience = 15;
    }
    public void show()
    {
        System.out.printf("Name: %s; Age: %s; Experience: %s\n", name, age, experience);
    }
}
