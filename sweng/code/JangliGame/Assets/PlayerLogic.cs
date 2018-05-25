using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class PlayerLogic : MonoBehaviour {

    public Text StoryTextField;
    static public string PlayerName;
    static public int MaxPlayerLives = 5;
    static public int PlayerScore;
    static public int PlayerLives;

    // Use this for initialization
    void Start () {
        GetStoryString();
        PlayerLives = MaxPlayerLives;
    }
	
	// Update is called once per frame
	void Update () {

	}

    public void InitPlayer ()
    {
        PlayerScore = 0;
        PlayerLives = 5;
    }


    public void GetStoryString ()
    {
        string story = "Jungle-" + PlayerName + " lives int the jungle. Cannibals have taken his lady, " +
            "and are already heating their badass cannibal pot to cook her. " +
            "'Jungle-" + PlayerName + " gonna take her home for cuddle action!' says Jungle-" + PlayerName + 
            ". Good luck!";

        StoryTextField.text = story;
    }

}
