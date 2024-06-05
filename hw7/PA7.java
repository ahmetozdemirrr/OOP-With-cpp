import java.util.ArrayList;
import java.util.List;

interface Visual {}
interface NonVisual {}

interface Playable 
{
	void info();
}

interface NonPlayable 
{
	void info();
}

interface Observer 
{
    void update(DatasetObject datasetObject);
}

abstract class DatasetObject 
{
    private String name;
    private String otherInfo;

    public DatasetObject(String name, String otherInfo) 
    {
        this.name = name;
        this.otherInfo = otherInfo;
    }

    public String getName() 
    {
        return name;
    }

    public String getOtherInfo()
    {
        return otherInfo;
    }

    public abstract void info();
}

class Audio extends DatasetObject implements NonVisual, Playable
{
	private String duration;

    public Audio(String name, String duration, String otherInfo) 
    {
        super(name, otherInfo);
        this.duration = duration;
    }

    public String getDuration()
    {
    	return duration;
    }

    @Override
    public void info()
    {
        System.out.println("Audio object: " + getName() + ", " + getDuration() + ", " + getOtherInfo());
    }
}

class Video extends DatasetObject implements Visual, Playable 
{
	private String duration;

    public Video(String name, String duration, String otherInfo)
    {
        super(name, otherInfo);
        this.duration = duration;
    }

    public String getDuration()
    {
    	return duration;
    }

    @Override
    public void info() 
    {
        System.out.println("Video object: " + getName() + ", "  + getDuration() + ", " + getOtherInfo());
    }
}

class Text extends DatasetObject implements NonVisual, NonPlayable 
{
    public Text(String name, String otherInfo) 
    {
        super(name, otherInfo);
    }

    @Override
    public void info() 
    {
        System.out.println("Text object: " + getName() + ", " + getOtherInfo());
    }
}

class Image extends DatasetObject implements Visual, NonPlayable 
{
	private String dimension;

    public Image(String name, String dimension, String otherInfo) 
    {
        super(name, otherInfo);
        this.dimension = dimension;
    }

    public String getDimension()
    {
    	return dimension;
    }

    @Override
    public void info() 
    {
        System.out.println("Image object: " + getName() + ", " + getDimension() + ", "+ getOtherInfo());
    }
}

class Dataset 
{
    private List<Observer> observers = new ArrayList<>();
    private List<DatasetObject> datasetObjects = new ArrayList<>();

    public void register(Observer observer) //adding player or viewer
    {
        observers.add(observer);
    }

    public void un_register(Observer observer) //remove player or viewer
    {
        observers.remove(observer);
    }

    public void add(DatasetObject datasetObject) //adding music-video-text-image
    {
        datasetObjects.add(datasetObject);
        notify_observers(datasetObject);
    }

    public void remove(DatasetObject datasetObject) //remove music-video-text-image
    {
        datasetObjects.remove(datasetObject);
        notify_observers(datasetObject); 
    }

    private void notify_observers(DatasetObject datasetObject) 
    {
        for (Observer observer : observers) 
        {
            observer.update(datasetObject);
        }
    }
}

class Player implements Observer 
{
    private List <Playable> playlist;
    private int currentIndex;

    public Player() 
    {
        playlist = new ArrayList<>();
        currentIndex = 0;
    }

    public void show_list() 
    {
        for (Playable playable : playlist) 
        {
            playable.info();
        }
    }

    public Playable currently_playing() //Finds and returns the currently playing element
    {
        if (currentIndex >= 0 && currentIndex < playlist.size()) //We return the element of the playlist in the desired index
        {
            return playlist.get(currentIndex);
        } 

        else 
        {
            return null;
        }
    }

    public void next(String type) 
    {
        currentIndex++;

        if (currentIndex >= playlist.size()) //If we want to move on to the next one, we reset the currentIndex and rewind if it is greater than our total length.
        {
            currentIndex = 0;
        }

        while (!controlType(playlist.get(currentIndex),type)) //If the type is not the type we want, we return in while until we move on to the next one.
        {
            currentIndex++;

            if (currentIndex >= playlist.size()) 
            {
                currentIndex = 0;
            }
        }
    }

    public void previous(String type) 
    {
        currentIndex--;

        if (currentIndex < 0) //If we have reached the first item in the list, we set the index length to one less than the list length.
        {
            currentIndex = playlist.size() - 1;
        }

        while (!controlType(playlist.get(currentIndex),type)) //We loop through until we find an element of the desired type.
        {
            currentIndex--;

            if (currentIndex < 0) 
            {
                currentIndex = playlist.size() - 1;
            }
        }
    }

    private boolean controlType(Playable playable, String type) //We find the class type of the incoming Playable object
    {
        if (type.equalsIgnoreCase("audio")) 
        {
            return playable instanceof Audio;
        } 

        else if (type.equalsIgnoreCase("video")) 
        {
            return playable instanceof Video;
        } 

        else 
        {
            return false;
        }
    }

    public void info() 
    {
        Playable currentlyPlaying = currently_playing();

        if (currentlyPlaying != null) 
        {
            currentlyPlaying.info();
        } 

        else 
        {
            System.out.println("There are no playable object currently playing.");
        }
    }

	@Override
	public void update(DatasetObject datasetObject)
	{
	    if (datasetObject instanceof Playable) //Add if it is an object of that class
	    {
	        playlist.add((Playable) datasetObject);
	    } 

	    else if (playlist.contains(datasetObject)) //delete that element if it already exists
	    {
	        playlist.remove(datasetObject);
	    }
	}
}

class Viewer implements Observer 
{
    private List<NonPlayable> viewList;
    private int currentIndex;

    public Viewer() 
    {
        viewList = new ArrayList<>();
        currentIndex = 0;
    }

    public void show_list() 
    {
        for (NonPlayable nonPlayable : viewList) 
        {
            nonPlayable.info();
        }
    }

    public NonPlayable currently_viewing() 
    {
        if (currentIndex >= 0 && currentIndex < viewList.size()) 
        {
            return viewList.get(currentIndex);
        } 

        else 
        {
            return null;
        }
    }

    public void next(String type) 
    {
        currentIndex++;

        if (currentIndex >= viewList.size()) 
        {
            currentIndex = 0;
        }

        while (!controlType(viewList.get(currentIndex), type)) 
        {
            currentIndex++;

            if (currentIndex >= viewList.size()) 
            {
                currentIndex = 0;
            }
        }
    }

    public void previous(String type) 
    {
        currentIndex--;

        if (currentIndex < 0) 
        {
            currentIndex = viewList.size() - 1;
        }

        while (!controlType(viewList.get(currentIndex), type)) 
        {
            currentIndex--;

            if (currentIndex < 0) 
            {
                currentIndex = viewList.size() - 1;
            }
        }
    }

    private boolean controlType(NonPlayable nonPlayable, String type) 
    {
        if (type.equalsIgnoreCase("text")) 
        {
            return nonPlayable instanceof Text;
        } 

        else if (type.equalsIgnoreCase("image")) 
        {
            return nonPlayable instanceof Image;
        } 

        else 
        {
            return false;
        }
    }

    public void info() 
    {
        NonPlayable currentlyViewing = currently_viewing();

        if (currentlyViewing != null) 
        {
            currentlyViewing.info();
        } 

        else 
        {
            System.out.println("There are no nonplayable object currently viewing.");
        }
    }

    @Override
	public void update(DatasetObject datasetObject) 
	{
	    if (datasetObject instanceof NonPlayable) 
	    {
	        viewList.add((NonPlayable) datasetObject);
	    } 

	    else if (viewList.contains(datasetObject)) 
	    {
	        viewList.remove(datasetObject);
	    }
	}
}

public class PA7 
{
    public static void main(String[] args) 
    {
        Dataset ds = new Dataset();

        Player p1 = new Player();
        Player p2 = new Player();

        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();

        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);

        ds.add(new Image("imagename1","dimension info1","other info1"));
        ds.add(new Image("imagename2","dimension info2","other info2"));
        ds.add(new Image("imagename3","dimension info3","other info3"));
        ds.add(new Image("imagename4","dimension info4","other info4"));
        ds.add(new Image("imagename5","dimension info5","other info5"));

        ds.add(new Audio("auidoname1","duration info1","other info1"));
        ds.add(new Audio("auidoname2","duration info2","other info2"));
        ds.add(new Audio("auidoname3","duration info3","other info3"));

        ds.add(new Video("videoname1","duration info1","other info1"));
        ds.add(new Video("videoname2","duration info2","other info2"));
        ds.add(new Video("videoname3","duration info3","other info3"));

        ds.add(new Text("textname1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

	    System.out.println("Player 1's Playlist:");
	    p1.show_list();

	    // Let's view the display list of the Viewer object
	    System.out.println("Viewer 1's View List:");
	    v1.show_list();

	    // Let's perform the next and previous operations on the Player object
	    System.out.println("Next Item in Player 1's Playlist:");
	    p1.next("audio");
	    p1.info();

	    System.out.println("Previous Item in Player 1's Playlist:");
	    p1.previous("video");
	    p1.info();

	    // Let's perform the next and previous operations on the Viewer object
	    System.out.println("Next Item in Viewer 1's View List:");
	    v1.next("text");
	    v1.info();

	    System.out.println("Previous Item in Viewer 1's View List:");
	    v1.previous("image");
	    v1.info();

	    // Let's remove items from Player and Viewer objects
	    Playable po = p1.currently_playing();
	    NonPlayable np = v1.currently_viewing();

	    ds.remove((DatasetObject) po);
	    ds.remove((DatasetObject) np);

	    // Let's view the updated playlist
	    System.out.println("Player 1's Updated Playlist:");
	    p1.show_list();

        System.out.println("\n\n");

        p2.show_list();
        p1.un_register();
        ds.add(new Video("videoname7","duration info7","other info7"));
        System.out.println("\n\n");

        p1.show_list();
        System.out.println("\n\n");
        
        p2.show_list();


        System.out.println("\n\n");

	    // Let's view the updated view list
	    System.out.println("Viewer 1's Updated View List:");
	    v1.show_list();

        /*Playable po = p1.currently_playing();

        po.info();

        ds.remove((DatasetObject)po);

        NonPlayable np = v1.currently_viewing();

        np.info();*/
    }
}