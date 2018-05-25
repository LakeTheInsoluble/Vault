using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapScrollL3 : MonoBehaviour {

    public GameObject Player;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        float xOffset = transform.position.x - Player.transform.position.x;
        float yOffset = Player.transform.position.y - transform.position.y;

        if (xOffset > 30f)
        {
            transform.position += new Vector3(-90f, 0f, 0f);
        }
   
        transform.position += new Vector3(0, yOffset, 0f);
    }
}
