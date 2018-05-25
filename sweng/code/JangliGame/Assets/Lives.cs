using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lives : MonoBehaviour {

    static public float lives = 5;

    void GainLife(int amount)
    {
        lives = lives + amount;
    }

    //Sould be used in handling life losing
    void LoseLife(int amount)
    {
        //TODO: finish life implementation now lives are reset every death
        print("LIVES LOST");
        lives = lives - amount;

        if (lives < 1)
        {
            PlayerLostAllLives();
        }
        //StartOver();
    }

    //Call this when all lifes are lost
    //TODO: finish implementation
    void PlayerLostAllLives()
    {
        //Call Game over screen
    }

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
