using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class platformsL3 : MonoBehaviour {

    public GameObject platformController;
    public GameObject platform;
    public float initX, initY;
    public int numOfPlatforms;
    public float heightInc, widthInc;


    // Use this for initialization
    void Start () {
        var p1 = platform.transform.TransformPoint(0, 0, 0);
        var p2 = platform.transform.TransformPoint(1, 1, 0);
        L3platformSpawn();
    }


    // Update is called once per frame
    void L3platformSpawn () {
        for (int i = 0; i < numOfPlatforms; i++)
        {
            Vector3 pos = new Vector3(initX, initY, 0);
            GameObject newPlatform = Instantiate(platform, pos, transform.rotation);
            newPlatform.transform.SetParent(platformController.transform);
            initX -= widthInc;
            initY += heightInc;
        }
    }
}
