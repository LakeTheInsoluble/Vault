using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class AirMeter : MonoBehaviour {

    public int startingOxygen = 1000;
    public int currentOxygen;
    public Slider oxygenSlider;

    public PlayerL2 player;

    // Use this for initialization
    void Start () {
 
    }
	
	// Update is called once per frame
	void Update () {
        currentOxygen -= 1 ;
        oxygenSlider.value = currentOxygen;

        if ( currentOxygen == 0)
        {
            Debug.Log("Happi loppui");
            player.SendMessage("LoseLife", 1);
        }
	}

    void Breathe()
    {
        currentOxygen = startingOxygen;
    }
}
