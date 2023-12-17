package repository;

import exceptions.FullRepositoryException;
import exceptions.TreeNotInRepositoryException;
import model.Tree;
public interface IRepository {
    abstract public void addTree(Tree tree) throws FullRepositoryException;

    abstract public void removeTree(int id) throws TreeNotInRepositoryException;

    abstract public Tree[] getTrees();

    abstract public int getSize();
}
