package web.domain;

public class Station {
    private int id;
    private int city1_id;
    private int city2_id;

    // Constructors
    public Station(int id, int city1Id, int city2Id) {
        this.id = id;
        this.city1_id = city1Id;
        this.city2_id = city2Id;
    }

    public Station(int city1Id, int city2Id) {
        this.city1_id = city1Id;
        this.city2_id = city2Id;
    }

    // Getters and setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getCity1Id() {
        return city1_id;
    }

    public void setCity1Id(int city1Id) {
        this.city1_id = city1Id;
    }

    public int getCity2Id() {
        return city2_id;
    }

    public void setCity2Id(int city2Id) {
        this.city2_id = city2Id;
    }

    // Override toString for easy debugging
    @Override
    public String toString() {
        return "Station{" +
                "id=" + id +
                ", city1Id=" + city1_id +
                ", city2Id=" + city2_id +
                '}';
    }
}

