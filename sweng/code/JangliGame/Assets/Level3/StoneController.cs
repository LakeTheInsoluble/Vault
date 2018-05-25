using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StoneController : MonoBehaviour
{

    public GameObject stoneController;
    public GameObject RollingStone;
    public GameObject Player;
    public float spawnTime;
    public float yOffset, xOffset;
    public float xGap;
    private float crocodileX = -110f;

    // Use this for initialization
    void Start()
    {
        InvokeRepeating("rollingStoneSpawn", 0, spawnTime);
    }

    void rollingStoneSpawn()
    {
        float y = Player.transform.position.y + yOffset;
        float x = Player.transform.position.x - xOffset;

        Vector3 pos = new Vector3(x, y, 0);
        GameObject newRollingStone = Instantiate(RollingStone, pos, transform.rotation);
        newRollingStone.transform.SetParent(stoneController.transform);
    }
}
