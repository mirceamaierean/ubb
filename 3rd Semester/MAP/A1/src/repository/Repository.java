package repository;

import exceptions.FullRepositoryException;
import exceptions.TreeNotInRepositoryException;
import model.Tree;
public class Repository implements IRepository {
    private Tree[] trees;
    public static int MAX_TREES = 100;
    private int size = 0;

    public Repository()
    {
        this.trees = new Tree[MAX_TREES];
    }

    public void addTree(Tree tree) throws FullRepositoryException {
        if (this.size >= MAX_TREES) {
            throw new FullRepositoryException("Repository is full");
        }
        this.trees[this.size++] = tree;
    }

    public void removeTree(int id) throws TreeNotInRepositoryException {
        for (int i = 0; i < this.size; i++) {
            if (this.trees[i].getId() == id) {
                for (int j = i; j < this.size - 1; j++) {
                    this.trees[j] = this.trees[j + 1];
                }
                this.trees[this.size - 1] = null;
                this.size--;
                return;
            }
        }
        throw new TreeNotInRepositoryException("Tree not in repository");
    }

    public Tree[] getTrees()
    {
        Tree[] trees = new Tree[this.size];
        System.arraycopy(this.trees, 0, trees, 0, this.size);
        return trees;
    }

    public int getSize()
    {
        return this.size;
    }
}
