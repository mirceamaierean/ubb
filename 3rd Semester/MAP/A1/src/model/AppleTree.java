package model;

public class AppleTree extends Tree{

    public AppleTree(int id, int age)
    {
        super(id, age);
    }

    @Override
    public String getTypeOfTree()
    {
        return "Apple Tree";
    }

    @Override
    public String toString()
    {
        return "Apple Tree with id " + this.id + " and age " + this.age;
    }
}
