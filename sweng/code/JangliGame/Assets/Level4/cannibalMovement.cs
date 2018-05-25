using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cannibalMovement : MonoBehaviour
{
    float speed = 1f;
    int timer = 0;
    int threshold = 1;
    bool direction = false;
    Rigidbody2D rb;
    SpriteRenderer sprite;
    Animator anim;
    PolygonCollider2D playerCollider;

    // Use this for initialization
    void Start () {
        rb = GetComponent<Rigidbody2D>(); // Get the rigidbody component added to the script and store it in rb
        sprite = GetComponent<SpriteRenderer>();
        anim = GetComponent<Animator>();
        playerCollider = GetComponent<PolygonCollider2D>();
    }

    void turn()
    {
        sprite.flipX = direction;
        threshold = Random.Range(50, 200);
        timer = 0;
        direction = direction != true;
        speed = Random.Range(2, 4);
    }
	
	// Update is called once per frame
	void Update () {
        timer += 1;

        if (timer > threshold)
        {
            turn();
        }

        if (direction)
        {
            rb.velocity = new Vector2(speed, rb.velocity.y);
        }
        else
        {
            rb.velocity = new Vector2(speed * -1, rb.velocity.y);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "cannibal")
        {
            turn();
        }
    }
}
