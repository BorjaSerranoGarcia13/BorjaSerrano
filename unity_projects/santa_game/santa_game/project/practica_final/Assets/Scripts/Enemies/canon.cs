using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class canon : MonoBehaviour
{
    public GameObject bulletPrefabs;
    public GameObject objetive;
    public Transform shootPoint;
    private Camera cam;
    [SerializeField]
    float hit_time=2;
    [SerializeField]
    float cadence = 2;
    float shoot;
    [SerializeField]
    float aggro_distance=15;
    float distance;
    public int poolMaxSize=10;
    List<GameObject> elementPoolList;

    // Start is called before the first frame update
    void Start()
    {
        cam = Camera.main;
        shoot = cadence;
        elementPoolList = new List<GameObject>();
        for (int i=0; i < poolMaxSize; i++)
        {
            GameObject obj = (GameObject) Instantiate(bulletPrefabs);
            obj.SetActive(false);
            elementPoolList.Add(obj);
        }

        if (objetive == null) {
            objetive = ((movement2) FindObjectOfType(typeof(movement2))).gameObject;
        }
    }
    GameObject GetPoolObject()
    {
        for (int i = 0; i < poolMaxSize; i++)
        {
            if (!elementPoolList[i].activeInHierarchy) {
                return elementPoolList[i];
            }
        }
        return null;
    }
    // Update is called once per frame
    void Update()
    {
        distance = Vector3.Distance(transform.position,objetive.transform.position);

        CanonRotation();
        if (distance < aggro_distance)
        {
            shoot -= Time.deltaTime;
            if (shoot <= 0)
            {
                LaunchProjectile();
                shoot = cadence;
            }
        }
    }
    void CanonRotation() {
        this.gameObject.transform.rotation = Quaternion.Slerp(this.gameObject.transform.rotation,
           Quaternion.LookRotation(objetive.transform.position - this.gameObject.transform.position), 1000 * Time.deltaTime);
    }



    void LaunchProjectile()
    {

        GameObject obj = GetPoolObject();
        obj.SetActive(true);

        obj.transform.position = shootPoint.position;
        obj.transform.rotation = Quaternion.identity;
        Rigidbody rg = obj.GetComponent<Rigidbody>();
        rg.velocity = CalculateVelocity(objetive.transform.position, shootPoint.position, hit_time);



    }
    Vector3 CalculateVelocity(Vector3 target, Vector3 origin, float time)
    {
        Vector3 distance = target - origin;
        Vector3 distanceXZ = distance;
        distanceXZ.y = 0f;

        float Sy = distance.y;
        float Sxz = distanceXZ.magnitude;

        float Vxz = Sxz / time;
        float Vy = Sy / time + 0.5f * Mathf.Abs(Physics.gravity.y)*time;

        Vector3 result = distanceXZ.normalized;
        result *= Vxz;
        result.y = Vy;
        return result;
    }
}
