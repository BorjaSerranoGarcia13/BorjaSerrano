using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.Advertisements;

public class Banner : MonoBehaviour
{

  private string playstoreID = "3593066";
  private string appstoreID = "3593067";

  private readonly string bannerPlacementId = "banner";


    // Start is called before the first frame update
    void Start()
    {
      if (Application.platform == RuntimePlatform.Android)
      {
        Advertisement.Initialize (playstoreID, true);
      }
      else if(Application.platform == RuntimePlatform.IPhonePlayer)
      {
        Advertisement.Initialize (appstoreID, true);
      }
      InitializeAdvertisement();

      Advertisement.Banner.SetPosition(BannerPosition.BOTTOM_CENTER);
      StartCoroutine(ShowBannerWhenReady());
    }

    private void InitializeAdvertisement()
    {
      if (Application.platform == RuntimePlatform.Android)
      {
            Advertisement.Initialize(playstoreID, true);
            return;
      }
        Advertisement.Initialize(appstoreID, true);
    }

    public IEnumerator ShowBannerWhenReady()
    {
        while (!Advertisement.IsReady(bannerPlacementId))
        {
            yield return new WaitForSeconds(0.1f);
        }

        Advertisement.Banner.Show(bannerPlacementId);
    }

    public void ActivateBanner()
    {
      Advertisement.Banner.Show(bannerPlacementId);
    }

    public void HideBanner()
    {
        Advertisement.Banner.Hide(false);
    }
}
