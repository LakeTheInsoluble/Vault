using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;



public class PlayerL1 : MonoBehaviour
{

	float speed = 6f;
    float distToGround;
    bool swinging = false;
    bool canSwing = true;
	bool underWater;
    bool dead;
    float deathY = -10f;
    Rigidbody2D rb;
	SpriteRenderer sprite;
	Animator anim;
	Vector2 startingPosition;
    PolygonCollider2D playerCollider;


    public float points;
    public Text pointsText;

    public Text pointsNumber;
    public Text livesNumber;

    // HITBOXES

    public Transform topLeftLeg;
    public Transform bottomRightLeg;
    public LayerMask groundLayers;

    //This view loads the first view again
    void StartOver()
    {
        SceneManager.LoadScene("JangliGame");
    }

    void nextScene()
    {
        SceneManager.LoadScene("WaterLevel");
    }

 //   void SetPointsText()
 //   {
 //       pointsText.text = points.ToString();
 //   }
 //
 //   void TakePoints(int amount)
 //   {
 //       points += amount;
 //       SetPointsText();
 //   }
 //
 //   void GivePoints(int amount)
 //   {
 //       points += amount;
 //       SetPointsText();
 //   }
 //
 //   void ZeroPoints()
 //   {
 //       points = 0;
 //   }

    // Use this for initialization
    void Start ()
	{
		rb = GetComponent<Rigidbody2D> (); // Get the rigidbody component added to the script and store it in rb
		sprite = GetComponent<SpriteRenderer> ();
		anim = GetComponent<Animator> ();
        playerCollider = GetComponent<PolygonCollider2D> ();
		startingPosition = transform.position;
        underWater = false;
        dead = false;

        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
        livesNumber.text = PlayerLogic.PlayerLives.ToString();
    }

    // Update is called once per frame
    void Update()
    {
        if (transform.position.x < -100)
        {
            nextScene();
        }

        if (swinging == false)
        {
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
            if (transform.position.y < deathY && !underWater)
            {
                print("You are dead");
                LoseLife();
                
            }

            if (!underWater)
            {
                anim.SetFloat("Speed", Mathf.Abs(movement));
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
        else
        {
            playerCollider.enabled = false;

            if (Input.GetKeyDown(KeyCode.Space))
            {
                swinging = false;
                Destroy(GetComponent<HingeJoint2D>());
                anim.SetTrigger(Animator.StringToHash("Jump"));
                rb.AddForce(new Vector2(0, 400));
                StartCoroutine(Wait());
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "wine" && canSwing == true)
        {
            canSwing = false;
            swinging = true;

            HingeJoint2D hinge = gameObject.AddComponent<HingeJoint2D>() as HingeJoint2D;
            hinge.connectedBody = collision.gameObject.GetComponent<Rigidbody2D>();

            AddScore();
        }

    }

    public void AddScore()
    {
        PlayerLogic.PlayerScore += 10;
        pointsNumber.text = PlayerLogic.PlayerScore.ToString();
    }

    public void LoseLife()
    {
        PlayerLogic.PlayerLives -= 1;
        livesNumber.text = PlayerLogic.PlayerLives.ToString();
        if ( PlayerLogic.PlayerLives <= 0)
        {
            SceneManager.LoadScene("GameOver");
        }
        else
        {
            StartOver();
        }
    }

    IEnumerator Wait()
    {
        yield return new WaitForSeconds(1.0f);
        canSwing = true;

        playerCollider.enabled = true;
    }

    bool IsGrounded()
    {
        print("grounded");
        return Physics2D.OverlapArea(topLeftLeg.position, bottomRightLeg.position, groundLayers);
    }
}
