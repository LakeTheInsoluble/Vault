using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BubbleController : MonoBehaviour {

    public GameObject bubbleController;
    public GameObject Bubble;

    public float spawnTime;
    public float minY;
    public float maxY;
    private float bubbleX = -18f;
    public float gapX;
    public List<GameObject> bubbleList;


    // Use this for initialization
    void Start () {
        InvokeRepeating("bubbleSpawn", 0, spawnTime);
    }
	
	// Update is called once per frame
	void bubbleSpawn () {
        float y = Random.Range(minY, maxY);
        bubbleX -= gapX;
        Vector3 pos = new Vector3(bubbleX, y, 0);
        GameObject newBubble = Instantiate(Bubble, pos, transform.rotation);
        newBubble.transform.SetParent(bubbleController.transform);
        bubbleList.Add(newBubble);
    }
}
