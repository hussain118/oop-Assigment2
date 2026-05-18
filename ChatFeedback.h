#ifndef CHATNOTE_H
#define CHATNOTE_H

#include <iostream>
#include <string>
using namespace std;

class ChatNote {
private:
    string noteID;
    string fromID;
    string toID;
    string body;
    string sentAt;
    bool opened;

    static int noteTotal;

public:

    ChatNote() {
        noteTotal++;
        noteID = "CHT" + to_string(noteTotal);
        fromID = "";
        toID = "";
        body = "";
        sentAt = "2026-01-01 00:00";
        opened = false;
    }

    ChatNote(string from, string to, string text, string time) {
        noteTotal++;
        noteID = "CHT" + to_string(noteTotal);
        fromID = from;
        toID = to;
        body = text;
        sentAt = time;
        opened = false;
    }

    ChatNote(const ChatNote& src) {
        noteTotal++;
        noteID = "CHT" + to_string(noteTotal);
        fromID = src.fromID;
        toID = src.toID;
        body = src.body;
        sentAt = src.sentAt;
        opened = src.opened;
    }

    void setFromID(string s) { fromID = s; }
    void setToID(string r) { toID = r; }
    void setBody(string c) { body = c; }
    void setSentAt(string t) { sentAt = t; }
    void flagAsOpened() { opened = true; }

    string getNoteID() const { return noteID; }
    string getFromID() const { return fromID; }
    string getToID() const { return toID; }
    string getBody() const { return body; }
    string getSentAt() const { return sentAt; }
    bool getOpened() const { return opened; }

    static int getNoteTotal() { return noteTotal; }

    void showNote() const {
        cout << "  [" << sentAt << "] From " << fromID
             << " -> " << toID << endl;
        cout << "  Content: " << body << endl;
        cout << "  Status : " << (opened ? "Opened" : "Unread") << endl;
    }

    bool sentBy(string id) const { return fromID == id; }

    string getPreview() const {
        return "[" + noteID + "] " + body.substr(0, 30) + "...";
    }

    void promptReply() const {
        cout << "Replying to chat from " << fromID << endl;
    }
};

int ChatNote::noteTotal = 0;

#endif

#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <iostream>
#include <string>
using namespace std;

class Feedback {
private:
    string feedbackID;
    string customerID;
    string dealerID;
    int stars;
    string remark;
    string postedOn;
    bool isConfirmed;

    static int feedbackTotal;

public:

    Feedback() {
        feedbackTotal++;
        feedbackID = "FBK" + to_string(feedbackTotal);
        customerID = "";
        dealerID = "";
        stars = 3;
        remark = "No remark";
        postedOn = "2026-01-01";
        isConfirmed = false;
    }

    Feedback(string cID, string dID, int rating, string text, string date) {
        feedbackTotal++;
        feedbackID = "FBK" + to_string(feedbackTotal);
        customerID = cID;
        dealerID = dID;
        stars = (rating >= 1 && rating <= 5) ? rating : 3;
        remark = text;
        this->postedOn = date;
        isConfirmed = false;
    }

    Feedback(const Feedback& src) {
        feedbackTotal++;
        feedbackID = "FBK" + to_string(feedbackTotal);
        customerID = src.customerID;
        dealerID = src.dealerID;
        stars = src.stars;
        remark = src.remark;
        postedOn = src.postedOn;
        isConfirmed = src.isConfirmed;
    }

    void setStars(int r) { if (r >= 1 && r <= 5) stars = r; }
    void setRemark(string c) { remark = c; }
    void confirmFeedback() { isConfirmed = true; }

    string getFeedbackID() const { return feedbackID; }
    int getStars() const { return stars; }
    string getRemark() const { return remark; }
    string getCustomerID() const { return customerID; }
    string getDealerID() const { return dealerID; }
    bool getIsConfirmed() const { return isConfirmed; }

    static int getFeedbackTotal() { return feedbackTotal; }

    void showFeedback() const {
        cout << "  Feedback ID : " << feedbackID << endl;
        cout << "  Stars       : " << stars << "/5" << endl;
        cout << "  Remark      : " << remark << endl;
        cout << "  Posted On   : " << postedOn << endl;
        cout << "  Confirmed   : " << (isConfirmed ? "Yes" : "Pending") << endl;
    }

    bool isGoodReview() const { return stars >= 4; }
    bool isBadReview() const { return stars <= 2; }
    string getStarLabel() const {
        if (stars == 5) return "Outstanding";
        if (stars == 4) return "Solid";
        if (stars == 3) return "Neutral";
        if (stars == 2) return "Below Par";
        return "Terrible";
    }
};

int Feedback::feedbackTotal = 0;

#endif
