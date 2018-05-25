using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrocodileController : MonoBehaviour
{
    public GameObject crocodileController;
    public GameObject Crocodile;
    public float spawnTime;
    public float yMin, yMax;
    public float xGap;
    private float crocodileX = -10f;
    public List<GameObject> crocodileList;

    void Start()
    {
        InvokeRepeating("crocoSpawn", 0, spawnTime);
    }

    void crocoSpawn()
    {
        float y = Random.Range(yMin, yMax);
        crocodileX -= xGap;
        Vector3 pos = new Vector3(crocodileX, y, 0);
        GameObject newCroco = Instantiate(Crocodile, pos, transform.rotation);
        newCroco.transform.SetParent(crocodileController.transform);
        crocodileList.Add(newCroco);
    }
}