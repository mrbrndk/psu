package com.company;

public class Head extends Person {
    private String name;
    private int age;
    private boolean secondment;
    public Head()
    {
        super();
        name = "Alexey";
        age = 47;
        secondment = true;
    }
    public void show()
    {
        System.out.printf("Name: %s; Age: %s; Secondment: %s\n", name, age, secondment);
    }
}
