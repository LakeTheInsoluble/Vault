using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Points : MonoBehaviour {

    static public float points = 100000;
    public Text pointsText;

    void SetPointsText()
    {
        pointsText.text = points.ToString();
    }

    void TakePoints(int amount)
    {
        points -= amount;
        SetPointsText();
    }

    void GivePoints(int amount)
    {
        points += amount;
        SetPointsText();
    }

    void ZeroPoints()
    {
        points = 0;
    }

    void SavePoints()
    {
        PlayerPrefs.SetFloat("Points", points);
    }

    // Use this for initialization
    void Start () {
        SetPointsText();
    }
	
	// Update is called once per frame
	void Update () {
        TakePoints(1);
        SetPointsText();
    }





}
