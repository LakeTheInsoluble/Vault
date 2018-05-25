using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class EndScreenLogic : MonoBehaviour {

    private string playerName;
    public Text EndingText;

	// Use this for initialization
	void Start () {
        playerName = PlayerLogic.PlayerName;

        string txt = "Jungle-" + playerName + " found his lady." +
    " Now they are heading to the shag og Jungle-" + playerName +
    " for long-longed cuddle action. Your final Score is " + PlayerLogic.PlayerScore.ToString();

        EndingText.text = txt;

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
