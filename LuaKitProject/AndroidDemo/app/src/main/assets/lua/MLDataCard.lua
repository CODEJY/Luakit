---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by wujiayu.
--- DateTime: 2018/12/5 7:51 PM
---
local TAG = "MLDataCard"
local mlDataSource = {}

local getRankTable = function()
    if mlDataSource ~= null then
        if mlDataSource["MLRank"] then
            local mlRank = cjson.decode(mlDataSource["MLRank"])
            return mlRank
        end
    end
end

local yogaBuilder = function(container)
    local mlRank = getRankTable()
    container.isEnabled = true
    container.alignItems = YGAlignCenter
    container.flexDirection = YGFlexDirectionColumn --垂直布局
    container.backgroundColor = { a = 1.0, r = 0.114, g = 0.122, b = 0.129 }

    local backgroundIv = container.addImageView()      --取值->添加图层关系： addImageView()
    backgroundIv.isEnabled = true
    backgroundIv.width = 334
    backgroundIv.height = 180
    backgroundIv.imagePath = 'tools_card_ml.png'

    local allContentContainer = container.addContainer()
    allContentContainer.width = 334
    allContentContainer.height = 180
    allContentContainer.marginTop = -180
    allContentContainer.alignItems = YGAlignCenter
    allContentContainer.flexDirection = YGFlexDirectionColumn

    local titleContainer = allContentContainer.addContainer()
    titleContainer.width = 334
    titleContainer.height = 45
    titleContainer.isEnabled = true
    titleContainer.alignItems = YGAlignCenter
    titleContainer.flexDirection = YGFlexDirectionColumn
    titleContainer.marginTop = 14

    local titleTv = titleContainer.addTextView()
    titleTv.width = 300
    titleTv.height = 20
    titleTv.text = "Mobile Legends"
    titleTv.textTable = {
        fontSize = 16,
        isBold = false,
        alignment = TextAlignmentCenter,
        color = { a = 1.0, r = 1.0, g = 1.0, b = 1.0 }
    }

    local userInfoContainer = allContentContainer.addContainer()
    userInfoContainer.isEnabled = true
    userInfoContainer.width = 334
    userInfoContainer.height = 66
    userInfoContainer.alignItems = YGAlignFlexStart
    userInfoContainer.flexDirection = YGFlexDirectionRow

    local userAvatarIv = userInfoContainer.addImageView()
    userAvatarIv.width = 46
    userAvatarIv.height = 46
    userAvatarIv.viewCornerRadius = 23
    if mlDataSource["userIcon"] then
        userAvatarIv.imagePath = mlDataSource["userIcon"]
    else
        userAvatarIv.imagePath = 'zz.png'
    end
    userAvatarIv.marginStart = 16

    local userNameContainer = userInfoContainer.addContainer()
    userNameContainer.width = 172
    userNameContainer.height = 36
    userNameContainer.alignItems = YGAlignFlexStart
    userNameContainer.flexDirection = YGFlexDirectionColumn
    userNameContainer.marginStart = 9
    userNameContainer.marginTop = 4

    local userNameTv = userNameContainer.addTextView()
    userNameTv.width = 172
    userNameTv.height = 18
    if mlDataSource.nickName then
        userNameTv.text = mlDataSource.nickName
    else
        userNameTv.text = "---"
    end
    userNameTv.textTable = {
        fontSize = 15,
        isBold = false,
        alignment = TextAlignmentLeft,
        color = { a = 1.0, r = 1.0, g = 1.0, b = 1.0 },
        numberOfLines = 1
    }

    local nearlyStatusContainer = userNameContainer.addContainer()
    nearlyStatusContainer.width = 172
    nearlyStatusContainer.height = 14
    nearlyStatusContainer.marginTop = 2
    nearlyStatusContainer.alignItems = YGAlignCenter
    nearlyStatusContainer.flexDirection = YGFlexDirectionRow

    local nearlyStatusIv = nearlyStatusContainer.addImageView()
    nearlyStatusIv.width = 12
    nearlyStatusIv.height = 12
    -- 读取最近上升还是下降
    nearlyStatusIv.imagePath = "stars_rise.png"

    local nearlyStatusTv = nearlyStatusContainer.addTextView()
    nearlyStatusTv.width = 172
    nearlyStatusTv.height = 18
    --读取最近等级状态
    nearlyStatusTv.text = "Nearly status:" .. " " .. "5" .. " " .. "stars"
    nearlyStatusTv.textTable = {
        fontSize = 12,
        isBold = false,
        alignment = TextAlignmentLeft,
        color = { a = 0.6, r = 1.0, g = 1.0, b = 1.0 }
    }

    local rankContainer = userInfoContainer.addContainer()
    rankContainer.width = 60
    rankContainer.height = 64
    rankContainer.marginStart = 15
    rankContainer.alignItems = YGAlignFlexStart
    rankContainer.flexDirection = YGFlexDirectionColumn

    local rankBgIv = rankContainer.addImageView()
    rankBgIv.width = 60
    rankBgIv.height = 52
    -- 根据等级匹配图片
    rankBgIv.imagePath = "rank_4.png"

    local rankIv = rankContainer.addImageView()
    rankIv.width = 60
    rankIv.height = 52
    rankIv.marginTop = -52
    -- 根据等级匹配图片
    rankIv.imagePath = "rank_master.png"

    local starsContainer = rankContainer.addContainer()
    starsContainer.width = 60
    starsContainer.height = 9
    starsContainer.alignItems = YGAlignFlexStart
    starsContainer.flexDirection = YGFlexDirectionRow
    starsContainer.justifyContent = YGJustifyCenter

    -- 根据星星数量增加星星数量
    if mlRank ~= null then
        local stars = mlRank["star"]
        if stars ~= null and stars > 0 then
            for i = 1, stars do
                local starsIv = starsContainer.addImageView()
                starsIv.width = 9
                starsIv.height = 9
                starsIv.imagePath = "star.png"
            end
        end
    end


    local dataContainer = allContentContainer.addContainer()
    dataContainer.width = 334
    dataContainer.height = 44
    dataContainer.marginTop = 6
    dataContainer.alignItems = YGAlignCenter
    dataContainer.justifyContent = YGJustifySpaceBetween
    dataContainer.flexDirection = YGFlexDirectionRow

    local dataSubContainerWidth = 82
    local dataSubContainerHeight = 44
    local textViewWidth = 82
    local textValueHeight = 22
    local textTipHeight = 16
    local dataSubContainerAlignItems = YGAlignCenter
    local dataSubContainerFlexDirection = YGFlexDirectionColumn
    local subContainerTextTable_Value = {
        fontSize = 18,
        alignment = TextAlignmentCenter,
        fontName = "DIN-Bold.otf",
        color = { a = 1.0, r = 1.0, g = 1.0, b = 1.0 }
    }

    local subContainerTextTable_Tip = {
        fontSize = 12,
        alignment = TextAlignmentCenter,
        color = { a = 0.6, r = 1.0, g = 1.0, b = 1.0 }
    }

    local winLossContainer = dataContainer.addContainer()
    winLossContainer.width = dataSubContainerWidth
    winLossContainer.height = dataSubContainerHeight
    winLossContainer.alignItems = dataSubContainerAlignItems
    winLossContainer.flexDirection = dataSubContainerFlexDirection

    local winLostValueTv = winLossContainer.addTextView()
    winLostValueTv.width = textViewWidth
    winLostValueTv.height = textValueHeight
    --读取最近十场胜负数
    winLostValueTv.text = "---"
    winLostValueTv.textTable = subContainerTextTable_Value

    local winLossTv = winLossContainer.addTextView()
    winLossTv.width = textViewWidth
    winLossTv.height = textTipHeight
    winLossTv.marginTop = 1
    --多语言
    winLossTv.text = "Win/Loss"
    winLossTv.textTable = subContainerTextTable_Tip

    local killsContainer = dataContainer.addContainer()
    killsContainer.width = dataSubContainerWidth
    killsContainer.height = dataSubContainerHeight
    killsContainer.alignItems = dataSubContainerAlignItems
    killsContainer.flexDirection = dataSubContainerFlexDirection

    local killsValueTv = killsContainer.addTextView()
    killsValueTv.width = textViewWidth
    killsValueTv.height = textValueHeight
    -- 最近十场最高击杀
    killsValueTv.text = "---"
    killsValueTv.textTable = subContainerTextTable_Value

    local killsTv = killsContainer.addTextView()
    killsTv.width = textViewWidth
    killsTv.height = textTipHeight
    killsTv.marginTop = 1
    -- 多语言
    killsTv.text = "Kills"
    killsTv.textTable = subContainerTextTable_Tip

    local assistsContainer = dataContainer.addContainer()
    assistsContainer.width = dataSubContainerWidth
    assistsContainer.height = dataSubContainerHeight
    assistsContainer.alignItems = dataSubContainerAlignItems
    assistsContainer.flexDirection = dataSubContainerFlexDirection

    local assistsValueTv = assistsContainer.addTextView()
    assistsValueTv.width = textViewWidth
    assistsValueTv.height = textValueHeight
    --最近十场最高助攻数
    assistsValueTv.text = "---"
    assistsValueTv.textTable = subContainerTextTable_Value

    local assistsTv = assistsContainer.addTextView()
    assistsTv.width = textViewWidth
    assistsTv.height = textTipHeight
    assistsTv.marginTop = 1
    --多语言
    assistsTv.text = "Assists"
    assistsTv.textTable = subContainerTextTable_Tip

    local ratingContainer = dataContainer.addContainer()
    ratingContainer.width = dataSubContainerWidth
    ratingContainer.height = dataSubContainerHeight
    ratingContainer.alignItems = dataSubContainerAlignItems
    ratingContainer.flexDirection = dataSubContainerFlexDirection

    local ratingValueTv = ratingContainer.addTextView()
    ratingValueTv.width = textViewWidth
    ratingValueTv.height = textValueHeight
    ratingValueTv.marginStart = -6
    --综合评分
    ratingValueTv.text = "---"
    ratingValueTv.textTable = subContainerTextTable_Value

    local ratingTv = ratingContainer.addTextView()
    ratingTv.width = textViewWidth
    ratingTv.height = textTipHeight
    ratingTv.marginStart = -6
    --多语言
    ratingTv.text = "Rating"
    ratingTv.textTable = subContainerTextTable_Tip

end

return yogaBuilder