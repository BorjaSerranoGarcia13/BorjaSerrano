using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeadHead : MonoBehaviour
{
    scoreCounter script;
    public bool deadhead;

    public AudioSource dead;
    // Start is called before the first frame update
    void Start()
    {
      script = GameObject.Find("CountScore").GetComponent<scoreCounter>();
      deadhead = false;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        Animator animator = GetComponentInParent<Animator>();
        if (other.gameObject.CompareTag("Player") && !deadhead)
        {
          script.total_score += 100f;
          animator.SetBool("dead", true);
          deadhead = true;
          dead.Play();
        }
      }
}
