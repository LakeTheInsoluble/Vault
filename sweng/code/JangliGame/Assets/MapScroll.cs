using UnityEngine;
using System.Collections;

public class MapScroll : MonoBehaviour {

    public GameObject Background;
	public GameObject Player;
    public Material jungle;
    public Material ocean;

	// Use this for initialization
	void Start () {
		//Add functionality here
	}
	
	// Update is called once per frame
	void Update () {
        MeshRenderer m = Background.GetComponent<MeshRenderer>();
        float xOffset = transform.position.x - Player.transform.position.x;
		if (xOffset > 30f) {
			transform.position +=  new Vector3(-90f, 0f, 0f);
		}
        if (transform.position.x < -100f)
        {
            m.material = ocean;
        }
	}
}
