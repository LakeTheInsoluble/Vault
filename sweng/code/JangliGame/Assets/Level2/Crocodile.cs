using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Crocodile : MonoBehaviour {
    // Use this for initialization
    void Start () {}

    // Update is called once per frame
    void Update() { }
    
    //Handle collision with a crocodile
    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.name == "Player")
        {
            Debug.Log("Crocodile collided with " + other.name);
            other.gameObject.SendMessage("LoseLife",1);
            other.gameObject.SendMessage("LoseLifeNew");
        }
    }

    // Leave here if needed
    void OnTriggerStay2D(Collider2D other){}
    void OnTriggerExit2D(Collider2D other)
    {

    }
}
