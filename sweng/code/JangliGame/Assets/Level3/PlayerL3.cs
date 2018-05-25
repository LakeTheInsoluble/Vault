using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayerL3 : MonoBehaviour
{

    int lives;

    float speed = 6f;
    float distToGround;
    Rigidbody2D rb;
    SpriteRenderer sprite;
    Animator anim;
    Vector2 startingPosition;
    PolygonCollider2D playerCollider;

    public Text pointsNumber;
    public Text livesNumber;

    // HITBOXES

    public Transform topLeftLeg;
    public Transform bottomRightLeg;
    public LayerMask groundLayers;

    private int scoreCounter;

    // Use this for initialization
    void Start()
    {
        rb = GetComponent<Rigidbody2D>(); // Get the rigidbody component added to the script and store it in rb
        sprite = GetComponent<SpriteRenderer>();
        anim = GetComponent<Animator>();
        playerCollider = GetComponent<PolygonCollider2D>();
        startingPosition = transform.position;

        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
        livesNumber.text = PlayerLogic.PlayerLives.ToString();

        scoreCounter = 0;
    }

    // Update is called once per frame
    void Update() {

        scoreCounter++;

        if ( scoreCounter >= 100)
        {
            AddScoreNew();
            scoreCounter = 0;
        }

        if (transform.position.x < -50) {
            nextScene();
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

        rb.velocity = new Vector2(movement, rb.velocity.y);

        if (Input.GetKeyDown(KeyCode.Space) && isGrounded())
        {
            anim.SetTrigger(Animator.StringToHash("Jump"));
            rb.AddForce(new Vector2(0, 400));
        }
    }

    bool isGrounded()
    {
        return Physics2D.OverlapArea(topLeftLeg.position, bottomRightLeg.position, groundLayers);
    }

    void LoseLife(int amount)
    {
        //TODO: finish life implementation now lives are reset every death
        print("LIVES LOST");
        lives = lives - amount;

        if (lives < 1)
        {
            PlayerLostAllLives();
        }
        StartOver();
    }

    void StartOver()
    {
        SceneManager.LoadScene("JangliGameL3");
    }

    void nextScene()
    {
        SceneManager.LoadScene("CannibalLevel");
    }

    void PlayerLostAllLives()
    {
        //Call Game over screen
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
        }
        else
        {
            StartOver();
        }
    }
}
