using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;



public class PlayerL2 : MonoBehaviour
{
    int lives;
	float speed = 6f;
    float distToGround;

    private int scoreCounter;

    //Variables for death
    bool underWater;
    bool dead;
    //Level 1
    const float deathMinY = -10f;
    const float deathMaxY = 10f;
    //Level 2
    //Add parameters here
    bool level2 = true;
    const float waterSurfaceLevel = 5.6f;


    Rigidbody2D rb;
	SpriteRenderer sprite;
	Animator anim;
	Vector2 startingPosition;
    PolygonCollider2D playerCollider;

    public Slider oxygenSlider;
    public Text pointsNumber;
    public Text livesNumber;

    // HITBOXES

    public Transform topLeftLeg;
    public Transform bottomRightLeg;
    public LayerMask groundLayers;

    //Call to increase gain lives

    void nextScene()
    {
        SceneManager.LoadScene("JangliGameL3");
    }


    void GainLife(int amount)
    {
        lives = lives + amount;
    }

    //Sould be used in handling life losing
    void LoseLife(int amount)
    {
        //TODO: finish life implementation now lives are reset every death
        print("LIVES LOST");
        lives = lives - amount;
        
        if(lives < 1)
        {
            PlayerLostAllLives();
        }
        StartOver();
    }


    //Call this when all lifes are lost
    //TODO: finish implementation
    void PlayerLostAllLives()
    {
        //Call Game over screen
    }

    //This view loads the first view again
    void StartOver()
    {
        SceneManager.LoadScene("WaterLevel");
    }

	// Use this for initialization
	void Start ()
	{
		rb = GetComponent<Rigidbody2D> (); // Get the rigidbody component added to the script and store it in rb
		sprite = GetComponent<SpriteRenderer> ();
		anim = GetComponent<Animator> ();
        playerCollider = GetComponent<PolygonCollider2D> ();
		startingPosition = transform.position;
        underWater = true;

        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
        livesNumber.text = PlayerLogic.PlayerLives.ToString();

        //Life and death
        dead = false;

        //TODO: get lifes that are left
        lives = 5;

        scoreCounter = 0;
    }

    // Update is called once per frame
    void Update ()
	{
        scoreCounter++;
        if ( scoreCounter >= 100)
        {
            AddScoreNew();
            scoreCounter = 0;
        }
        // Implementation for death from falling on jumping mode

        if (transform.position.x < -100)
        {
            nextScene();
        }

        if (transform.position.y < deathMinY && !level2)
        {
            LoseLife(1);
            LoseLifeNew();
        }

        // Implementation for death on Y limits
        if (transform.position.y < deathMinY || transform.position.y > deathMaxY)
        {
            LoseLife(1);
            LoseLifeNew();
        }

        // Implementation for underwater area
        if (transform.position.x < -110f && transform.position.y < waterSurfaceLevel)
        {
            underWater = true;
        }

        if (transform.position.y > waterSurfaceLevel)
        {
            underWater = false;
        }

		var input = Input.GetAxis ("Horizontal"); // This will give us left and right movement (from -1 to 1). 
        var inputY = Input.GetAxis("Vertical");
        var movement = input * speed;
        var movementY = inputY * speed;
		if (!underWater) {
            anim.SetFloat ("Speed", Mathf.Abs (movement));
        }

		if (Input.GetKeyDown (KeyCode.LeftArrow)) {
            if (underWater)
            {
                sprite.flipX = false;
            }
            else
            {
                sprite.flipX = true;
            }
		}

        if (rb.position.y < 5)
        {
            rb.velocity = new Vector2 (movement + -5f, movementY);
        } else
        {
            oxygenSlider.SendMessage("Breathe");
            rb.velocity = new Vector2(movement + -5f, -1f);
        }

        if (underWater)
        {
            anim.SetTrigger(Animator.StringToHash("Swim"));
        }
	}

bool isGrounded()
    {
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
        }
        else
        {
            StartOver();
        }
    }

}
