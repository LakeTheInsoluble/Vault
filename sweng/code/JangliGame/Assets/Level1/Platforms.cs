using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platforms : MonoBehaviour {
    public GameObject platformController;
    public GameObject platform;
    public float spawnTime;
    public float yMin, yMax;
    public float xGap;
    private float platformX = 0;

    void Start()
    {
        InvokeRepeating("platformSpawn", 0, spawnTime);
    }

    void platformSpawn()
    {
        if (platformX > -110f)
        {
            float y = Random.Range(yMin, yMax);
            platformX -= xGap;
            Vector3 pos = new Vector3(platformX, y, 0);
            GameObject newPlatform = Instantiate(platform, pos, transform.rotation);
            newPlatform.transform.SetParent(platformController.transform);
        }
    }
}
 