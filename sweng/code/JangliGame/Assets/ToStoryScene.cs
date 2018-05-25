using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ToStoryScene : MonoBehaviour {

    public InputField NameInputField;
 

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void OnClick ()
    {
        string playerName = NameInputField.text.ToString();
        PlayerLogic.PlayerName = playerName;
        PlayerLogic.PlayerLives = PlayerLogic.MaxPlayerLives;
        PlayerLogic.PlayerScore = 0;
        SceneManager.LoadScene("JangliStory");
    }
}
