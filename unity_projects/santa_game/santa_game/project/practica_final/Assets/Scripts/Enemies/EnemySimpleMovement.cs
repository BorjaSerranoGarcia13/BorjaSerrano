using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySimpleMovement : MonoBehaviour
{
    [SerializeField]
    float moveSpeed = 5;  
    public Animator animator;
    public bool on_movement = true;
    CheckGround ckground;
    public bool attacking = false;
    public bool follow=true;
    // Start is called before the first frame update
    void Start()
    {
        ckground = gameObject.GetComponent<CheckGround>();
    }

    // Update is called once per frame
    void Update()
    {
        if (ckground != null)
        {
            if (ckground.IsOnGround() != attacking)
            {
                on_movement = true;
            }
            else
            {
                on_movement = false;
            }
            if (on_movement && follow)
            {
                animator.SetBool("walk", true);
                this.gameObject.transform.position += this.gameObject.transform.forward * moveSpeed * Time.deltaTime;
            }
            else animator.SetBool("walk", false);
        }
        else { this.gameObject.transform.position += this.gameObject.transform.forward * moveSpeed * Time.deltaTime; }
    }
}
