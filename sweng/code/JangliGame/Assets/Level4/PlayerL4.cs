using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;



public class PlayerL4 : MonoBehaviour
{
    float speed = 6f;
    bool dead;
    float deathY = -10f;
    Rigidbody2D rb;
    SpriteRenderer sprite;
    Animator anim;
    Vector2 startingPosition;
    PolygonCollider2D playerCollider;

    // HITBOXES

    public Transform topLeftLeg;
    public Transform bottomRightLeg;
    public LayerMask groundLayers;

    public Text pointsNumber;
    public Text livesNumber;

    private int scoreCounter;
    //This view loads the first view again
    void StartOver()
    {
        SceneManager.LoadScene("CannibalLevel");
    }

    void Win()
    {
        print("you are wiener?");
        SceneManager.LoadScene("EndScreen");
    }

    // Use this for initialization
    void Start()
    {
        rb = GetComponent<Rigidbody2D>(); // Get the rigidbody component added to the script and store it in rb
        sprite = GetComponent<SpriteRenderer>();
        anim = GetComponent<Animator>();
        playerCollider = GetComponent<PolygonCollider2D>();
        startingPosition = transform.position;
        dead = false;

        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
        livesNumber.text = PlayerLogic.PlayerLives.ToString();

        scoreCounter = 0;
    }

    // Update is called once per frame
    void Update()
    {

        scoreCounter++;

        if (scoreCounter >= 100)
        {
            AddScoreNew();
            scoreCounter = 0;
        }

        var input = Input.GetAxis("Horizontal"); // This will give us left and right movement (from -1 to 1). 
        var movement = input * speed;
        anim.SetFloat("Speed", Mathf.Abs(movement));

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            sprite.flipX = true;
        }

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            sprite.flipX = false;
        }
        //Implementation for death from falling on jumping mode
        if (transform.position.y < deathY)
        {
            LoseLifeNew();
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            sprite.flipX = true;
        }

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            sprite.flipX = false;
        }

        rb.velocity = new Vector2(movement, rb.velocity.y);
        if (Input.GetKeyDown(KeyCode.Space) && IsGrounded())
        {
            anim.SetTrigger(Animator.StringToHash("Jump"));
            rb.AddForce(new Vector2(0, 400));
        }

    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "wife")
        {
            Win();
        }
        if (collision.gameObject.tag == "cannibal")
        {
            LoseLifeNew();
        }
    }

    bool IsGrounded()
    {
        print("grounded");
        return Physics2D.OverlapArea(topLeftLeg.position, bottomRightLeg.position, groundLayers);
    }

    public void AddScoreNew()
    {
        PlayerLogic.PlayerScore += 10;
        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
    }

    public void LoseLifeNew()
    {
        PlayerLogic.PlayerLives -= 1;
        livesNumber.text = PlayerLogic.PlayerLives.ToString();
        if (PlayerLogic.PlayerLives <= 0)
        {
            SceneManager.LoadScene("GameOver");
        } else
        {
            StartOver();
        }
    }
}
