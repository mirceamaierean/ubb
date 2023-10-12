package model;

public abstract class Tree {
    protected int age, id;
    public Tree(int id, int age)
    {
        this.id = id;
        this.age = age;
    }

    public abstract String getTypeOfTree();

    public void setAge(int age)
    {
        this.age = age;
    }

    public int getAge()
    {
        return this.age;
    }

    public int getId()
    {
        return this.id;
    }
}
