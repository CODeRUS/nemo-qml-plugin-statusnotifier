# nemo-qml-plugin-statusnotifier
org.freedesktop.StatusNotifier specification implementation for Mer.
Based on LXQt sources, I appreciate that.

## Example usage:
On host side:
```
import org.nemomobile.statusnotifier 1.0

// ...

StatusNotifierModel {
    id: snModel
}

// ...

SilicaListView
{

// ...

    model: snModel
    delegate: // Some delegate

// notifierItem is the only delegate role
// notifierItem type of StatusNotifierIcon

//   notifierItem.status: StatusNotifierIcon.Passive / StatusNotifierIcon.Active / StatusNotifierIcon.NeedsAttention
//   notifierItem.title: string
//   notifierItem.icon: string
//   notifierItem.overlayIcon: string
//   notifierItem.attentionIcon: string

//   notifierItem.activate()
//   notifierItem.secondaryActivate()
//   notifierItem.scroll(int delta, Qt::Orientation orientation)

}
```

On client side:
```
import org.nemomobile.statusnotifier 1.0

// ...

StatusNotifierItem {
    id: snItem
    status: StatusNotifierItem.Passive / StatusNotifierItem.Active / StatusNotifierItem.NeedsAttention
    title: "Some Title"
    icon: "image://theme/icon-m-passive-icon"
    overlayIcon: "image://theme/icon-m-active-icon"
    attentionIcon: "image://theme/icon-m-attention-icon"

    onActivateRequested: {
        // host triggered activate()
    }

    onSecondaryActivateRequested: {
        // host triggered secondaryActivate()
    }

    onScrollRequested: {
        // host triggered scroll()
    }
}
```
