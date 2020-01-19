package com.company;

public class Student extends Person {
    private String name;
    private int age;
    private int course;
    public Student()
    {
        super();
        name = "Viktor";
        age = 22;
        course = 2;
    }
    public void show()
    {
        System.out.printf("Name: %s; Age: %s; Course: %s\n", name, age, course);
    }
}
