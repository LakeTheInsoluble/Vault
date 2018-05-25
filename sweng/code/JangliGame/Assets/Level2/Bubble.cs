using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bubble : MonoBehaviour {

    private float speed;

    private int counter;
    public int counterLimit;

    public float killY;

	// Use this for initialization
	void Start () { 
        speed = Random.Range(0.005f, 0.02f);
        counter = 0;
    }
	
	// Update is called once per frame
	void Update () {
        Vector3 pos = transform.position;
        Quaternion rot = transform.rotation;

        if (pos.y >= killY) {
            Destroy(this);
        } else {
            pos.y += speed;
            transform.SetPositionAndRotation(pos, rot);
        }
	}

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.name == "Player")
        {
            Debug.Log("Bubble collided with player");
        }
    }

    void OnTriggerStay2D(Collider2D other) {
        if (other.gameObject.name == "Player" && counter <= counterLimit)
        {
            Debug.Log("colliding with player");
            Vector3 pos = transform.position;
            Quaternion rot = transform.rotation;
            pos.x -= 0.1f;
            transform.SetPositionAndRotation(pos, rot);
            other.gameObject.transform.position = transform.position;
            counter++;
        }
    }
}
