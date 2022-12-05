using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDead : MonoBehaviour
{
    public bool player_dead;
    private GameObject player;
    Vector3 scale;
    // ANIMATION
    private Animator animator;

    Collider m_Collider;

    public AudioSource aa;

    bool first_dead;

    // Start is called before the first frame update
    void Start()
    {
        scale = new Vector3(10,10,0);
        player_dead = false;
        animator = GetComponent<Animator>();
        player = GameObject.FindWithTag("Player");

        animator.SetBool("dead", false);

        m_Collider = GetComponent<Collider>();

        first_dead = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (player_dead || animator.GetBool("dead"))
        {
          if (!first_dead)
          {
            aa.Play();
            first_dead = true;
          }
          animator.SetBool("dead", true);
          player.transform.localScale += scale * Time.deltaTime;

          m_Collider.enabled = false;
          Destroy(GetComponent<PJ_Movement>());
        }
    }
}
